#include "gui/views/viewport.hpp"
#include "program.hpp"
#include "shaders.hpp"

ViewportWindow::ViewportWindow() {
  glGenFramebuffers(1, &m_fbo);
  glGenTextures(1, &m_color_texture);
  glGenRenderbuffers(1, &m_rbo);
  update_fbo();
}

void ViewportWindow::draw() {
  bind_fbo();
  Program::setMat4_id(Shaders::get_shader("main"), "vp", m_scene.cam.matrix);
  m_scene.render();
  unbind_fbo();

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoTitleBar);

  this->pos = ImGui::GetWindowPos();
  this->size = ImGui::GetContentRegionAvail();

    ImGui::Image((void*)m_color_texture,
                 ImVec2(size.x, size.y),
                 ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
    ImGui::PopStyleVar();
}

void ViewportWindow::bind_fbo()
{
  glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
  glViewport(0, 0, size.x, size.y);
}

void ViewportWindow::unbind_fbo()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ViewportWindow::update_fbo()
{

  glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

  glBindTexture(GL_TEXTURE_2D, m_color_texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         m_color_texture, 0);


  glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
                        size.x, size.y);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                            GL_RENDERBUFFER, m_rbo);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  	printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
