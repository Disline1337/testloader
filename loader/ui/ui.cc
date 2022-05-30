#include "ui.hh"

void ui::pre() {
    if (!globals.active) return;

    loadstyle();

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowBgAlpha(1.0f);
    ImGui::SetWindowSize(window_size);

    ImGui::InputText("Username", globals.user_name, IM_ARRAYSIZE(globals.user_name));
    ImGui::InputText("Password", globals.pass_word, IM_ARRAYSIZE(globals.pass_word), ImGuiInputTextFlags_Password);
    if (ImGui::Button("Login")) {
        //DO YOUR LOGIN HERE
    }
}

void ui::main() {
    {
        ImGui::Text("Welcome back");
        ImGui::Text("Subscription expire:");
        if (ImGui::Button("Load")) {
            //DO YOUR LOGIN HERE
        }
    }

}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;

    // colors
    ImGui::StyleColorsDark();

    if (window_pos.x == 0) {
        RECT screen_rect{};
        GetWindowRect(GetDesktopWindow(), &screen_rect);
        screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
        window_pos = (screen_res - window_size);

        // init images here
    }
}

void ui::loadstyle() {
    ImGuiStyle& m_Style = ImGui::GetStyle();

    m_Style.WindowRounding = 6.f;
    m_Style.WindowPadding.x = 10.f;
    m_Style.FrameRounding = 6.0f;

    m_Style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    m_Style.ItemSpacing = ImVec2(8, 4);
    m_Style.AntiAliasedLines = true;

    m_Style.Colors[ImGuiCol_WindowBg] = ImColor(128, 128, 128);
    m_Style.Colors[ImGuiCol_TitleBg] = ImColor(192, 192, 192);
    m_Style.Colors[ImGuiCol_TitleBgActive] = ImColor(200, 200, 200);
    m_Style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(200, 200, 200);
    m_Style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
    m_Style.Colors[ImGuiCol_Button] = ImColor(200, 200, 200);
    m_Style.Colors[ImGuiCol_ButtonActive] = ImColor(190, 190, 190);
    m_Style.Colors[ImGuiCol_ButtonHovered] = ImColor(210, 210, 210);

    ImGui::GetStyle() = m_Style;
}