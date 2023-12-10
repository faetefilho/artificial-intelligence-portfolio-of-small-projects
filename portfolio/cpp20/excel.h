#pragma once
#include <string>
#include <vector>

using namespace std;

class Excel
{
public:
    void run();
    void drawWindow(string windowName);
    void setImGuiStyleColors();

private:
    //int sliderRowValues{ 0 };
    int minRows{ 0 };
    int maxRows{ 30 };
    int currentRows{ 0 };

    int minColumns{ 0 };
    int maxColumns{ 30 };
    int currentColumns{ 0 };

    vector<vector<float>> data;
    vector<float> rowSum;
    vector<float> colSum;

    static constexpr auto popupFlags = ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoScrollbar;
    static constexpr auto popupSize = ImVec2(300.f, 100.f);
    static constexpr auto popuButtonSize = ImVec2(120.f, 0.f);
    static constexpr auto popupPos = ImVec2(1280.f / 2.f -popupSize.x / 2.f, 720.f / 2.f -popupSize.y / 2.f);

    bool graphVisible{ false };

    char fileNameBuffer[256]{"numbers.excel"};


private:
    void addRemoveButtons();
    void drawTable();
    template<typename T>
    void cellValue(string formatter, const T value);
    void valuePopup(const int row, const int col);
    void setPopupLayout();
    void calculateSum();
    void drawGraphButton();
    void drawGraph();
    void openSaveButtons();
    void savePopup();
    void saveFile(string fileName);
    void loadPopup();
    void loadFile(string filename);
};

template<typename T>
inline void Excel::cellValue(string formatter, const T value)
{
    ImGui::TableNextColumn();
    ImGui::Text(formatter.data(), value);
}
