#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "Globals.h"
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"
#include "Logger.h"

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // Enable Docking

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(App->GetWindow()->window, App->GetOpenGL()->GetContext());
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    showDemoWindow = false;
    showAboutWindow = false;
    showHardwareWindow = false;
    showWindowOptions = false;

    return true;
}

update_status ModuleEditor::PreUpdate(float deltaTime)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float deltaTime)
{
    
    RenderUI(deltaTime);
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate(float deltaTime)
{
    
    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void ModuleEditor::RenderUI(float deltaTime) {

    // Your other UI elements here
    DrawMenuBar();  
    DrawFpsGraph(deltaTime);

    if (showAboutWindow) {
        AboutWindow();  // Show the About window
    }
    if (showHardwareWindow) {
        DrawHardware();
    }
    if (showWindowOptions) {
        DrawWindowOptions();
    }
    DrawConsole();

}



void ModuleEditor::DrawMenuBar() {
        // Menu bar
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {

                if (ImGui::MenuItem("New")) {
                    // New action
                }
                if (ImGui::MenuItem("Open")) {
                    // Open action
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Settings")) {
                if (ImGui::MenuItem("Window", nullptr, showWindowOptions)) {
                    showWindowOptions = !showWindowOptions;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("About")) {
                // Correctly toggle the state of showAboutWindow
                if (ImGui::MenuItem("About", nullptr, showAboutWindow)) {
                    showAboutWindow = !showAboutWindow;
                }
                
                if (ImGui::MenuItem("Hardware", nullptr, showHardwareWindow)) {
                    showHardwareWindow = !showHardwareWindow;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }        
}


void ModuleEditor::AboutWindow()
{

    ImGui::Begin("StreetLights Engine", &showAboutWindow);


    ImGui::BulletText("A 3D graphics engine made by a master's student.");
    ImGui::Separator();
    ImGui::BulletText("GitHub Link: ");
    ImGui::SameLine();  // Keep text and link on the same line
    if (ImGui::Selectable("https://github.com/srLlobet/Engine")) {
        ShellExecuteA(nullptr, "open", "https://github.com/srLlobet/Engine", nullptr, nullptr, SW_SHOWNORMAL);
    }
    ImGui::Separator();
    ImGui::Text("AUTHOR");
    ImGui::Separator();
    ImGui::BulletText("Joan Llobet: ");
    ImGui::SameLine();
    if (ImGui::Selectable("https://github.com/srLlobet")) {
        ShellExecuteA(nullptr, "open", "https://github.com/srLlobet", nullptr, nullptr, SW_SHOWNORMAL);
    }
    ImGui::Separator();
    ImGui::Text("LIBRARIES");
    ImGui::Separator();
    ImGui::BulletText("Glew v2.2.0");
    ImGui::BulletText("OpenGL v4.6.0");
    ImGui::BulletText("ImGui v1.91.6");
    ImGui::BulletText("MathGeoLib");
    ImGui::BulletText("SDL v2.0.16");

    ImGui::Separator();
    ImGui::Text("LICENSE\n");
    ImGui::Separator();

    ImGui::Text("MIT License\n\n");
    ImGui::Text("Copyright (c) 2024 srLlobet");
    ImGui::Text("\n");
    ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the 'Software'), to deal \n");
    ImGui::Text("in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell \n");
    ImGui::Text("copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions : \n");
    ImGui::Text("\n");
    ImGui::Text("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n");
    ImGui::Text("\n");
    ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, \n");
    ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER \n");
    ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE \n");
    ImGui::Text("SOFTWARE.\n");

    ImGui::End();

}

void ModuleEditor::DrawFpsGraph(float deltaTime)
{
    float fps = (deltaTime > 0.0f) ? 1.0f / deltaTime : 0.0f;
    float ms = deltaTime * 1000.0f; // milliseconds per frame

    // Add FPS and Milliseconds to respective logs and cycle data if needed
    if (fps_log.size() >= maxFpsSamples) {
        fps_log.erase(fps_log.begin());  // Remove oldest entry
        ms_log.erase(ms_log.begin());    // Remove oldest entry
    }
    fps_log.push_back(fps);  // Add the new FPS value
    ms_log.push_back(ms);    // Add the new Milliseconds value

    if (fps_log.size() > 1000) fps_log.erase(fps_log.begin());
    if (ms_log.size() > 1000) ms_log.erase(ms_log.begin());

    // Create titles for FPS and Milliseconds
    char title[25];
    sprintf_s(title, 25, "Framerate %.1f", fps_log.back());
    ImGui::PlotHistogram("###framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));

    sprintf_s(title, 25, "Milliseconds %.1f", ms_log.back());
    ImGui::PlotHistogram("###milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));

    // FPS Limit Slider
    static float fpsLimit = 60.0f;
    if (ImGui::SliderFloat("Max FPS", &fpsLimit, 30.0f, 120.0f)) {
        // limitfps
    }


    static char organizationName[100] = "UPC";  // Default organization name
    static char version[50] = "v1.0.0";  // Default version
    ImGui::InputText("Organization Name", organizationName, IM_ARRAYSIZE(organizationName));
    ImGui::InputText("Version", version, IM_ARRAYSIZE(version));

    ImGui::Text("Current FPS: %.1f", fps);
    ImGui::Text("Frame Time: %.1f ms", ms);
}

void ModuleEditor::DrawConsole() {
    static bool isConsoleOpen = true;

    if (isConsoleOpen) {
        if (ImGui::Begin("Console", &isConsoleOpen)) {
            if (ImGui::Button("Clear")) {
                Logger::Instance().Clear();;
 }

            ImGui::Separator();

            for (const auto& line : Logger::Instance().GetLogs()) {
                ImGui::TextUnformatted(line.c_str());
            }
        }
        ImGui::End();
    }
}

void ModuleEditor::DrawHardware() {
    ImGui::Begin("Hardware Information", &showHardwareWindow);

    int major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    GLint memorySize = 0;
    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &memorySize);  // Example for NVIDIA GPU

    ImGui::Text("OpenGL Version: %d.%d", major, minor);
    ImGui::Text("Vendor: %s", vendor);
    ImGui::Text("Renderer: %s", renderer);
    ImGui::Text("GPU Memory: %d MB", memorySize / (1024 * 1024));  // Convert bytes to megabytes

    ImGui::End();
}

void ModuleEditor::DrawWindowOptions() {
     ImGui::Begin("Window Options", &showWindowOptions);

     static int screenWidth = App->GetOpenGL()->GetScreenWidth();
     static int screenHeight = App->GetOpenGL()->GetScreenHeight();

     ImGui::InputInt("Screen Width", &screenWidth);
     ImGui::InputInt("Screen Height", &screenHeight);

     if (ImGui::Button("Apply")) {

         SDL_Event resizeEvent;
         resizeEvent.type = SDL_WINDOWEVENT;
         resizeEvent.window.event = SDL_WINDOWEVENT_RESIZED;
         resizeEvent.window.data1 = screenWidth; // new width
         resizeEvent.window.data2 = screenHeight; // new height
         SDL_PushEvent(&resizeEvent);

     }

     ImGui::End();
}

