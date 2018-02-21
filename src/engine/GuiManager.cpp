#include "GuiManager.h"

#include "Shader.h"
#include "TextureData.h"
#include "Component.h"

#if defined(GLES2)
#include <GLES2/gl2.h>
#elif defined(GLES3)
#include <GLES3/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/gtx/transform.hpp>

TextureData *m_textureData;
Shader *m_shader;
static int g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

void GuiManager::addInputCharactersUTF8(const char *text)
{
  ImGuiIO &io = ImGui::GetIO();
  io.AddInputCharactersUTF8(text);
}

void GuiManager::setKeyEvent(int key, bool keydown)
{
  ImGuiIO &io = ImGui::GetIO();
  io.KeysDown[key] = keydown;
}

void GuiManager::renderDrawLists(ImDrawData *draw_data)
{
  // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
  ImGuiIO &io = ImGui::GetIO();
  int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
  int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
  if (fb_width == 0 || fb_height == 0)
    return;
  draw_data->ScaleClipRects(io.DisplayFramebufferScale);

  // Backup GL state
  GLint last_program;
  glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
  GLint last_texture;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
  GLint last_active_texture;
  glGetIntegerv(GL_ACTIVE_TEXTURE, &last_active_texture);
  GLint last_array_buffer;
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
  GLint last_element_array_buffer;
  glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
#if !defined(GLES2)
  GLint last_vertex_array;
  glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
  GLint last_blend_src;
  glGetIntegerv(GL_BLEND_SRC, &last_blend_src);
  GLint last_blend_dst;
  glGetIntegerv(GL_BLEND_DST, &last_blend_dst);
#endif
  GLint last_blend_equation_rgb;
  glGetIntegerv(GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb);
  GLint last_blend_equation_alpha;
  glGetIntegerv(GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha);
  GLint last_viewport[4];
  glGetIntegerv(GL_VIEWPORT, last_viewport);
  GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
  GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
  GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
  GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

  // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
  glEnable(GL_BLEND);
  glBlendEquation(GL_FUNC_ADD);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_SCISSOR_TEST);
  glActiveTexture(GL_TEXTURE0);

  // Setup orthographic projection matrix
  glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
  auto ortho_projection = glm::ortho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f);
  m_shader->bind();
  m_shader->setUniform1i("Texture", 0);
  m_shader->setUniformMatrix4f("ProjMtx", ortho_projection);
#if !defined(GLES2)
  glBindVertexArray(g_VaoHandle);
#else
  glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
  glEnableVertexAttribArray(g_AttribLocationPosition);
  glEnableVertexAttribArray(g_AttribLocationUV);
  glEnableVertexAttribArray(g_AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t) & (((TYPE *)0)->ELEMENT))
  glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid *)OFFSETOF(ImDrawVert, pos));
  glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid *)OFFSETOF(ImDrawVert, uv));
  glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid *)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF
#endif

  for (int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList *cmd_list = draw_data->CmdLists[n];
    const ImDrawIdx *idx_buffer_offset = 0;

    glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.size() * sizeof(ImDrawVert), (GLvoid *)&cmd_list->VtxBuffer.front(), GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx), (GLvoid *)&cmd_list->IdxBuffer.front(), GL_STREAM_DRAW);

    for (const ImDrawCmd *pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++)
    {
      if (pcmd->UserCallback)
      {
        pcmd->UserCallback(cmd_list, pcmd);
      }
      else
      {
        m_textureData->bind(0);
        glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
        glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
      }
      idx_buffer_offset += pcmd->ElemCount;
    }
  }

#if defined(GLES2)
  glDisableVertexAttribArray(g_AttribLocationPosition);
  glDisableVertexAttribArray(g_AttribLocationUV);
  glDisableVertexAttribArray(g_AttribLocationColor);
#endif

  // Restore modified GL state
  glUseProgram(last_program);
  glActiveTexture(last_active_texture);
  glBindTexture(GL_TEXTURE_2D, last_texture);
#if !defined(GLES2)
  glBindVertexArray(last_vertex_array);
#endif
  glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
  glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
#if !defined(GLES2)
  glBlendFunc(last_blend_src, last_blend_dst);
#endif
  if (last_enable_blend)
    glEnable(GL_BLEND);
  else
    glDisable(GL_BLEND);
  if (last_enable_cull_face)
    glEnable(GL_CULL_FACE);
  else
    glDisable(GL_CULL_FACE);
  if (last_enable_depth_test)
    glEnable(GL_DEPTH_TEST);
  else
    glDisable(GL_DEPTH_TEST);
  if (last_enable_scissor_test)
    glEnable(GL_SCISSOR_TEST);
  else
    glDisable(GL_SCISSOR_TEST);
  glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
}

void GuiManager::invalidateDeviceObjects(void)
{
#if !defined(GLES2)
  if (g_VaoHandle)
    glDeleteVertexArrays(1, &g_VaoHandle);
#endif
  if (g_VboHandle)
    glDeleteBuffers(1, &g_VboHandle);
  if (g_ElementsHandle)
    glDeleteBuffers(1, &g_ElementsHandle);
  g_VaoHandle = g_VboHandle = g_ElementsHandle = 0;

  delete m_shader;
}

void GuiManager::createDeviceObjects(void)
{
  m_shader = new Shader("shaders/gui");
  m_shader->link();
  m_shader->createUniform("Texture");
  m_shader->createUniform("ProjMtx");

  g_AttribLocationPosition = glGetAttribLocation(m_shader->getProgram(), "Position");
  g_AttribLocationUV = glGetAttribLocation(m_shader->getProgram(), "UV");
  g_AttribLocationColor = glGetAttribLocation(m_shader->getProgram(), "Color");

  glGenBuffers(1, &g_VboHandle);
  glGenBuffers(1, &g_ElementsHandle);

#if !defined(GLES2)
  glGenVertexArrays(1, &g_VaoHandle);
  glBindVertexArray(g_VaoHandle);

  glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
  glEnableVertexAttribArray(g_AttribLocationPosition);
  glEnableVertexAttribArray(g_AttribLocationUV);
  glEnableVertexAttribArray(g_AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t) & (((TYPE *)0)->ELEMENT))
  glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid *)OFFSETOF(ImDrawVert, pos));
  glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid *)OFFSETOF(ImDrawVert, uv));
  glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid *)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF
#endif
}

GuiManager::GuiManager(const glm::vec2 &drawableSize, const glm::vec2 &displaySize, SDL_Window *sdlWindow)
{
  m_sdlWindow = sdlWindow;

  showProps = true;

  ImGuiIO &io = ImGui::GetIO();
  io.KeyMap[ImGuiKey_Tab] = SDLK_TAB; // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
  io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
  io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
  io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
  io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
  io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
  io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
  io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
  io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
  io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
  io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
  io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
  io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
  io.KeyMap[ImGuiKey_A] = SDLK_a;
  io.KeyMap[ImGuiKey_C] = SDLK_c;
  io.KeyMap[ImGuiKey_V] = SDLK_v;
  io.KeyMap[ImGuiKey_X] = SDLK_x;
  io.KeyMap[ImGuiKey_Y] = SDLK_y;
  io.KeyMap[ImGuiKey_Z] = SDLK_z;

  io.RenderDrawListsFn = GuiManager::renderDrawLists; // Alternatively you can set this to NULL and call ImGui::GetDrawData() after ImGui::Render() to get the same ImDrawData pointer.
  io.SetClipboardTextFn = Window::setClipboardText;
  io.GetClipboardTextFn = Window::getClipboardText;

  //#ifdef _WIN32
  //  SDL_SysWMinfo wmInfo;
  //  SDL_VERSION(&wmInfo.version);
  //  SDL_GetWindowWMInfo(m_sdlWindow, &wmInfo);
  //  io.ImeWindowHandle = wmInfo.info.win.window;
  //#endif

  createDeviceObjects();

  unsigned char *pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height); // Load as RGBA 32-bits for OpenGL3 demo because it is more likely to be compatible with user's existing shader.
  m_textureData = new TextureData(width, height, pixels, GL_TEXTURE_2D, GL_LINEAR);

  io.DisplaySize = ImVec2(displaySize.x, displaySize.y);
  io.DisplayFramebufferScale = ImVec2(displaySize.x > 0 ? (drawableSize.x / displaySize.x) : 0, displaySize.y > 0 ? (drawableSize.y / displaySize.y) : 0);
}

GuiManager::~GuiManager(void)
{
  invalidateDeviceObjects();
  delete m_textureData;
  ImGui::Shutdown();
}

void GuiManager::tick(Window *window, std::chrono::microseconds delta)
{
  ImGuiIO &io = ImGui::GetIO();

  io.DeltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(delta).count();

  glm::vec2 mousePos = window->getInput()->getMousePosition();
  io.MousePos = ImVec2(mousePos.x, mousePos.y);

  io.MouseDown[0] = window->getInput()->mouseIsPressed(SDL_BUTTON_LEFT);
  io.MouseDown[1] = window->getInput()->mouseIsPressed(SDL_BUTTON_RIGHT);
  io.MouseDown[2] = window->getInput()->mouseIsPressed(SDL_BUTTON_MIDDLE);

  io.MouseWheel = window->getInput()->getMouseWheel().y / 15.0f;

  io.KeyShift = (window->getInput()->getKeyModState() & KMOD_SHIFT) != 0;
  io.KeyCtrl = (window->getInput()->getKeyModState() & KMOD_CTRL) != 0;
  io.KeyAlt = (window->getInput()->getKeyModState() & KMOD_ALT) != 0;
  io.KeySuper = (window->getInput()->getKeyModState() & KMOD_GUI) != 0;

  window->drawCursor(io.MouseDrawCursor ? false : true);

  // Start the frame
  ImGui::NewFrame();
}

void renderComponent(Component *component)
{
  ImGui::PushID(component);
  ImGui::AlignFirstTextHeightToWidgets();

  ImGui::PushStyleColor(ImGuiCol_Text, ImColor(1.0f, 0.78f, 0.58f, 1.0f));
  bool node_open = ImGui::TreeNodeEx("Component", ImGuiTreeNodeFlags_DefaultOpen, "%s_%u", "component", component);
  ImGui::NextColumn();
  ImGui::AlignFirstTextHeightToWidgets();
  ImGui::Text(component->getType());
  ImGui::PopStyleColor();
  ImGui::NextColumn();

  int id = 0;

  if (node_open)
  {
    for (auto &property : component->m_properties)
    {
      ImGui::PushID(id++);

      ImGui::AlignFirstTextHeightToWidgets();
      ImGui::Bullet();
      ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0.78f, 0.58f, 1.0f, 1.0f));
      ImGui::Selectable(property.first);
      ImGui::NextColumn();
      ImGui::PushItemWidth(-1);

      switch (property.second.type)
      {
      case FLOAT:
        ImGui::SliderFloat("##value", (float *)property.second.p, property.second.min, property.second.max);
        break;
      case FLOAT3:
        ImGui::SliderFloat3("##value", (float *)property.second.p, property.second.min, property.second.max);
        break;
      case BOOLEAN:
        ImGui::Checkbox("##value", (bool *)property.second.p);
        break;
      case COLOR:
        ImGui::ColorEdit3("##value", (float *)property.second.p);
        break;
      case ANGLE:
        ImGui::SliderAngle("##value", (float *)property.second.p, property.second.min, property.second.max);
        break;
      }
      ImGui::PopStyleColor();

      ImGui::PopItemWidth();
      ImGui::NextColumn();

      ImGui::PopID();
    }
    ImGui::TreePop();
  }
  ImGui::PopID();
}

void renderSceneGraph(Entity *sceneGraph)
{
  ImGui::PushID(sceneGraph);
  ImGui::AlignFirstTextHeightToWidgets();

  ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0.78f, 1.0f, 0.58f, 1.0f));
  bool node_open = ImGui::TreeNodeEx("Node", ImGuiTreeNodeFlags_DefaultOpen, "%s_%u", "node", sceneGraph);
  ImGui::PopStyleColor();
  ImGui::NextColumn();
  ImGui::AlignFirstTextHeightToWidgets();
  ImGui::NextColumn();

  int id = 0;

  if (node_open)
  {
    ImGui::PushID(id);
    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(0.0f, 0.8f, 1.0f, 1.0f));

    ImGui::AlignFirstTextHeightToWidgets();
    ImGui::Bullet();
    ImGui::Selectable("translation");
    ImGui::NextColumn();
    ImGui::PushItemWidth(-1);
    ImGui::SliderFloat3("##value", &(sceneGraph->getTransform().m_position.x), -10.0f, 10.0f);
    ImGui::PopItemWidth();
    ImGui::NextColumn();

    ImGui::PopID();
    ImGui::PushID(++id);

    ImGui::Bullet();
    ImGui::Selectable("rotation");
    ImGui::NextColumn();
    ImGui::PushItemWidth(-1);
    ImGui::SliderFloat4("##value", &(sceneGraph->getTransform().m_rotation.x), -1.0f, 1.0f);
    ImGui::PopItemWidth();
    ImGui::NextColumn();

    ImGui::PopID();
    ImGui::PushID(++id);

    ImGui::Bullet();
    ImGui::Selectable("scale");
    ImGui::NextColumn();
    ImGui::PushItemWidth(-1);
    ImGui::SliderFloat3("##value", &(sceneGraph->getTransform().m_scale.x), 0.0f, 10.0f);
    ImGui::PopItemWidth();
    ImGui::NextColumn();

    ImGui::PopStyleColor();
    ImGui::PopID();

    for (auto component : sceneGraph->getComponents())
    {
      renderComponent(component.get());
    }

    for (auto entity : sceneGraph->getChildren())
    {
      renderSceneGraph(entity.get());
    }

    ImGui::TreePop();
  }

  ImGui::PopID();
}

void GuiManager::togglePropertyEditor(void)
{
  showProps = !showProps;
}

void GuiManager::render(Entity *sceneGraph)
{
  if (showProps)
  {
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize(ImVec2(500, 0), ImGuiSetCond_FirstUseEver);
    if (!ImGui::Begin("Example: Fixed Overlay", nullptr, ImVec2(0, 0), 0.3f, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings))
    {
      ImGui::End();
      return;
    }
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
    ImGui::Separator();
    ImGui::Columns(2);

    renderSceneGraph(sceneGraph);

    ImGui::Columns(1);
    ImGui::Separator();
    ImGui::PopStyleVar();
    ImGui::End();

    // ImGui::ShowTestWindow();

    ImGui::Render();
  }
}
