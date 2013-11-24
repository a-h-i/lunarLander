#include "project_headers.hpp"
#include "utility.hpp"
#include "data.hpp"
#include "ui.hpp"
#include <fstream>
#include <cstdint>
#include <array>



static const std::string UI_SHADER_DIR("shaders/ui");




struct ui::FuelView::FViewImpl {
    GLuint program, vao, matrixID;
    GLuint vbos[2];
    static constexpr int VERTEX_ATTRIB = 0;
    static constexpr int COLOR_ATTRIB = 1;
    static constexpr std::size_t VERTEX_VBO = 0;
    static constexpr std::size_t COLOR_VBO = 1;
    static constexpr std::size_t OUTER_BYTE_OFFSET = 0;
    static constexpr std::size_t INNER_BYTE_OFFSET = data::fuel_outer_size * sizeof(glm::vec2);
    static constexpr std::size_t OUTER_OFFSET = 0;
    static constexpr std::size_t INNER_OFFSET = data::fuel_outer_size;
    static constexpr std::size_t INNER_MAX_VERT = 12;
    float prevFuelLevel;
    bool isFirst;
    std::size_t prevCount;
    std::array<glm::vec2, INNER_MAX_VERT> innerVertices;


    FViewImpl(): prevFuelLevel(), isFirst(true), prevCount(0) {
        //load shaders
        program = utility::loadShader(UI_SHADER_DIR + "/vertex.glsl", UI_SHADER_DIR + "/frag.glsl");
        setupArrays();
        innerVertices[0] = data::fuel_tank_outer[data::fuel_outer_size - 1];
        innerVertices[1] = data::fuel_tank_outer[0];
        matrixID = glGetUniformLocation(program, "mvp");

    }

    ~FViewImpl() {
        glDeleteProgram(program);
        glDeleteBuffers(2, vbos);
    }

    void draw(const float fuelLevel, glm::mat4 &mvp) {

        glUseProgram(program);
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
        glBindVertexArray(vao);
        // draw inner fill
        auto count = generateInner(fuelLevel);
        glBindBuffer(GL_ARRAY_BUFFER, vbos[VERTEX_VBO]);
        glBufferSubData(GL_ARRAY_BUFFER, INNER_BYTE_OFFSET, count * sizeof(glm::vec2), 
                        &innerVertices[0]);
        glDrawArrays(GL_TRIANGLES, INNER_OFFSET , count);

        // draw outer shell
        glDrawArrays( GL_LINE_LOOP, OUTER_OFFSET , data::fuel_outer_size);

   
        glUseProgram(0);
        glBindVertexArray(0);

    }
    private:
        void setupArrays();
        std::size_t generateInner(const float fuelLevel);
        std::size_t generateHelper(const float fuelLevel);
};






std::size_t ui::FuelView::FViewImpl::generateInner(const float fuelLevel) {
    if(isFirst) {
        prevCount = generateHelper(fuelLevel);
        prevFuelLevel = fuelLevel;
        isFirst = false;
        return prevCount;
    }else {
        if(fuelLevel != prevFuelLevel){
            prevCount = generateHelper(fuelLevel);
            prevFuelLevel = fuelLevel;
            return prevCount; 
        }else {
            return prevCount;
        }
    }
}



std::size_t ui::FuelView::FViewImpl::generateHelper(const float fuelLevel) {

    // ~!!!!!!!! WARNING !!!!!!!!~
    // ugly hack because apparently polygon is depricated 
    // and I don't feel like making indices
    // Sorry :<

    // draw left part ends
    static constexpr float LEFT_PERCENT = 0.9f;
    static constexpr float RIGHT_PERCENT = 0.1f;
    const float leftX = innerVertices[0].x  + utility::math::clamp(fuelLevel / LEFT_PERCENT, 1.0f, 0.0f);   
    innerVertices[2] = glm::vec2( leftX, innerVertices[1].y);
    innerVertices[3] = innerVertices[2];
    innerVertices[4] = glm::vec2(leftX, innerVertices[0].y);
    innerVertices[5] = innerVertices[0];
    
    //draw right part ends
    if(fuelLevel >= LEFT_PERCENT) {

        const float percent = 1.0f - ((1.0f - fuelLevel) * (RIGHT_PERCENT * 100.0f));
        const float deltaX = (data::fuel_tank_outer[3].x - data::fuel_tank_outer[2].x ) * percent;
        const float minX = data::fuel_tank_outer[2].x;
        const float maxX = minX + deltaX;
        const float topY = data::fuel_tank_outer[3].y;
        const float buttomY = data::fuel_tank_outer[4].y;

        //first triangle
        innerVertices[6] = glm::vec2(minX, buttomY);
        innerVertices[7] = glm::vec2(minX, topY);
        innerVertices[8] = glm::vec2(maxX, topY);
        //second triangle
        innerVertices[9] = glm::vec2(maxX, topY);
        innerVertices[10] = glm::vec2(maxX, buttomY);
        innerVertices[11] = glm::vec2(minX, buttomY);
        // left + right
        return 12;
    }else {
        // just left part
       return 6;
    }
}

void ui::FuelView::FViewImpl::setupArrays() {

        // create vertex array object
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        //Create Buffers
        glGenBuffers(2, vbos);
        //Setup vertex VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbos[VERTEX_VBO]);
        constexpr std::size_t vertexCount = data::fuel_outer_size + INNER_MAX_VERT;
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(glm::vec2),
                    nullptr, GL_STREAM_DRAW );
        //copy outer vertices
        glBufferSubData(GL_ARRAY_BUFFER, OUTER_BYTE_OFFSET, data::fuel_outer_size * sizeof(glm::vec2),
                         &data::fuel_tank_outer[0]);
        // inner vertices left for draw function
        glVertexAttribPointer(VERTEX_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(VERTEX_ATTRIB);
        // setup color vbo
        glBindBuffer(GL_ARRAY_BUFFER, vbos[COLOR_VBO]);
        // red shell
        std::vector<glm::vec4> colors(vertexCount);
        for(std::size_t i = 0; i < data::fuel_outer_size ; i++ ) {
            colors[i] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        }

        for(auto i = data::fuel_outer_size ; i < colors.size(); i++ ) {
            colors[i] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        }
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4) ,&colors[0], GL_STATIC_DRAW);
        glVertexAttribPointer(COLOR_ATTRIB, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(COLOR_ATTRIB);
        //unbind VAO
        glBindVertexArray(0);

}


ui::FuelView::FuelView(FuelControl &fc) : fc(fc), impl(new FViewImpl) {}

void ui::FuelView::draw() {
    static glm::mat4 translate = glm::translate(glm::mat4(), glm::vec3( -0.87f  , 
        0.9f, 0.0f));
    static glm::mat4 scale = glm::scale(glm::mat4(), glm::vec3(0.25, 0.25 , 1.0f));
    static glm::mat4 model = translate * scale;
    static glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
    static glm::mat4 mvp = projection * model;
    impl->draw(fc.status(), mvp);
}

ui::FuelView::~FuelView() {
    delete impl;
}