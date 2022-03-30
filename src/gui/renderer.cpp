#include "gui/renderer.hpp"

Renderer::Renderer()
{
    this->program = new Program("main");

    initVAO();
    initVBO();
    initEBO();

    glVertexAttribPointer(0, 3, 
            GL_FLOAT, GL_FALSE,
            3 * sizeof(float), 
            (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::applyCam()
{
    this->program->setMat4("mvp", this->camera->matrix);
}

void Renderer::update(int w, int h){
    std::cout << "Resize " << w << "x" << 
        h << '\n';

    this->w = w;
    this->h = h;

    glViewport(0, 0, w, h);

    if(this->camera) {
        this->camera->update(w, h);
        std::cout << "Push Matrix\n";
        program->setMat4("mvp", camera->matrix);
    } 


}

void Renderer::setCam(Camera &camera)
{
    this->camera = &camera;
}

void Renderer::draw()
{

    for(Element *element: childs)
    {
        element->draw();
    }
}

void Renderer::prepare()
{
    std::cout << "Bv: " << 
        this->bigger->vertices << 
        " Bi: " << this->bigger->indices <<
        '\n';

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 
            this->bigger->vertices * sizeof(float),
            nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            this->bigger->indices * sizeof(unsigned int),
            nullptr, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    this->program->use();

    if(this->camera) this->camera->update(w, h);
}

void Renderer::initVAO(){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void Renderer::initVBO(){
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Renderer::initEBO(){
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Renderer::add(Element *element) {
    this->childs.push_back(element);
    if (!this->bigger) this->bigger = element;
    if (this->bigger->vertices < element->vertices)
        this->bigger = element;
}

