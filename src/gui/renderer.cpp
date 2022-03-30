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

void Renderer::update(int w, int h){
    std::cout << "Resize " << w << "x" << 
        h << '\n';

    this->w = w;
    this->h = h;

    glViewport(0, 0, w, h);

    if (this->cam3d) {
        cam3d->update(w,h);
        this->program->setMat4("p", cam3d->projection);
    }

}

void Renderer::setCam3d(Cam3D &cam)
{
    this->cam3d = &cam;
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

    if(this->cam3d) this->cam3d->update(w, h);
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

void Renderer::sendView() {
        this->cam3d->view = glm::lookAt(this->cam3d->pos, 
                this->cam3d->pos + this->cam3d->front,
                this->cam3d->up);
    this->program->setMat4("v", this->cam3d->view);
}
