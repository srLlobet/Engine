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

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
    
    ImGui::ShowDemoWindow();

    DrawConsole();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    
    return UPDATE_CONTINUE;
}

bool ModuleEditor::cleanup()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return false;
}

void ModuleEditor::DrawConsole() {
    static bool isConsoleOpen = true;

    if (isConsoleOpen) {
        if (ImGui::Begin("Console", &isConsoleOpen)) {
            if (ImGui::Button("Clear")) {
                logger->Clear();
 }

            ImGui::Separator();

            for (const auto& line : logger->GetLogs()) {
                ImGui::TextUnformatted(line.c_str());
            }
        }
        ImGui::End();
    }
}
