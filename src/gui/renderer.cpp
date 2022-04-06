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

    this->w = initWidth;
    this->h = initHeight;

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
        this->biggerVertices << 
        " Bi: " << this->biggerIndices <<
        '\n';

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 
            this->biggerVertices * sizeof(float),
            nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
            this->biggerIndices * sizeof(unsigned int),
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
/* Bigger element pointer is not working, so instead we will declare two size_t 
 * 
 * The problem faced is that Cube doesn't use indices and it's the bigger element,
 * so the biggest indices memory reserved does not cover all elements in the renderer.
 * For instance 3dRect can't be drawn because it needs 6 indices to work. */

void Renderer::add(Element *element) {
    this->childs.push_back(element);
    if (!this->biggerIndices) this->biggerIndices = element->indices;
    if (this->biggerIndices < element->indices)
        this->biggerIndices = element->indices;

    if (!this->biggerVertices) this->biggerVertices = element->vertices;
    if (this->biggerVertices < element->vertices)
        this->biggerVertices = element->vertices;
}

void Renderer::sendView() {
        this->cam3d->view = glm::lookAt(this->cam3d->pos, 
                this->cam3d->pos + this->cam3d->front,
                this->cam3d->up);
    this->program->setMat4("v", this->cam3d->view);
}
