#include "excel.h"
#include "Imgui.h"
#include <vector>
#include <fstream>
#include <sstream>

void Excel::run()
{
    // draw 
    drawWindow("hello to this excel demo app");
}

void Excel::drawWindow(string windowName)
{
    // setting for initial/main window
    static constexpr auto windowFlags = ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoScrollbar;

    // window postition and size
    ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
    ImGui::SetNextWindowSize(ImVec2(1280.f, 720.f));

    ImGui::Begin(windowName.data(), nullptr, windowFlags);

    addRemoveButtons();
    ImGui::Separator();
    drawTable();
    ImGui::Separator();
    drawGraphButton();
    ImGui::Separator();
    drawGraph();
    openSaveButtons();
    ImGui::End();

}

void Excel::addRemoveButtons()
{
    bool addRow{ false };
    bool addColumn{ false };
    bool removeRow{ false };
    bool removeColumn{ false };

    auto sliderRowValues = currentRows;
    auto sliderColumnValues = currentColumns;

    // ----- rows section ------
    ImGui::Text("Number of rows:    ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##number of rows", &sliderRowValues, minRows, maxRows))
    {
        addRow = sliderRowValues > currentRows;
        removeRow = sliderRowValues < currentRows;
        currentRows = sliderRowValues;
    }

    ImGui::SameLine();
    if (ImGui::Button("Add row") && currentRows < maxRows)
    {
        ++currentRows;
        addRow = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove row") && currentRows > 0)
    {
        --currentRows;
        removeRow = true;
    }
    // ----- columns section ------
    ImGui::Text("Number of columns: ");
    ImGui::SameLine();
    if (ImGui::SliderInt("##number of columns", &sliderColumnValues, minColumns, maxColumns))
    {
        addColumn = sliderColumnValues > currentColumns;
        removeColumn = sliderColumnValues < currentColumns;
        currentColumns = sliderColumnValues;
    }

    ImGui::SameLine();
    if (ImGui::Button("Add column") && currentColumns < maxColumns)
    {
        ++currentColumns;
        addColumn = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove column") && currentColumns > 0)
    {
        --currentColumns;
        removeColumn = true;
    }
    //---------- table data section ----------
    if (addRow)
    {
        // Create a new vector of float elements, initializing it with a size equal to 'currentColumns' 
        // and setting all elements to the value 0.0f. This creates a new row of zeros.
        auto newRow = vector<float>(currentColumns, 0.0f);
        // Append the newly created 'newRow' to the end of the 'data' vector
        data.push_back(newRow);
    }
    // vunerability: clicking add/remove at the same time
    else if (removeRow)
    {
        // Loop until the number of rows in 'data' is reduced to the value 'currentRows'
        while (data.size() > static_cast<size_t>(currentRows))
        {
            data.pop_back();
        }
    }

    if (addColumn)
    {
        // Iterate through each row of the data
        for (auto& row : data)
        {
            // Increase the size of the current row to 'currentColumns'
            row.resize(currentColumns, 0.0f);
        }
        // Resize the vector that stores the sum of the columns to the new size 'currentColumns'
        colSum.resize(currentColumns, 0.0f);
    }
    else if (removeColumn)
    {
        for (auto& row : data)
        {
            row.resize(currentColumns, 0.0f);
        }
        colSum.resize(currentColumns, 0.0f);
    }
    
}

void Excel::drawTable()
{
    constexpr static auto tableFlags = ImGuiTableFlags_BordersV
        | ImGuiTableFlags_BordersOuter;
    static auto rowClicked = 0;
    static auto colClicked = 0;

    if (currentColumns == 0)
    {
        return;
    }
    // header of the table
    ImGui::BeginTable("Table", currentColumns, tableFlags);

    for (int32_t col = 0; col < currentColumns; col++)
    {
        const char* colName{ "A" };
        ImGui::TableSetupColumn(colName, ImGuiTableColumnFlags_WidthFixed, 1280.f / static_cast<float>(currentColumns));
    }
    ImGui::TableNextRow();
    for (int32_t col{ 0 }; col < currentColumns; col++)
    {
        ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(ImGuiCol_Header));
        cellValue("%c", 'A' + col);
    }

    //draw table rows
    for (int32_t row{ 0 }; row < currentRows; row++)
    {
        for (int32_t col{ 0 }; col < currentColumns; col++)
        {
            cellValue("%f", data[row][col]);
            if (ImGui::IsItemClicked())
            {
                ImGui::OpenPopup("change value");
                rowClicked = row;
                colClicked = col;
            }
            else if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Cell: (%d, %d", row, col);
            }
            //
            //

        }
        ImGui::TableNextRow();
    }
    valuePopup(rowClicked, colClicked);
    ImGui::TableNextRow();

    for (int32_t col{ 0 }; col < currentColumns; col++)
    {
        ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(ImGuiCol_Header));
        ImGui::TableSetColumnIndex(col);
        ImGui::Text("%f", colSum[col]);
    }

    ImGui::EndTable();
}

void Excel::valuePopup(const int row, const int col)
{
        setPopupLayout();
    if (ImGui::BeginPopupModal("change value", nullptr, popupFlags))
    {
        //setPopupLayout();
        //ImGui::SetNextWindowPos(popupPos);
        ImGui::Text("editing cell (%d, %d", row, col);
        float newValue = data[row][col];
        if (ImGui::InputFloat("##cellValue", &newValue))
        {
            data[row][col] = newValue;
        }
        if (ImGui::Button("OK"))
        {
            //update sum of each columns right after OK button is pressed
            calculateSum();
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

}

void Excel::setPopupLayout()
{
    ImGui::SetNextWindowSize(popupSize);
    ImGui::SetNextWindowPos(popupPos);

}

void Excel::calculateSum()
{
    // Initialize the rowSum vector with 'currentRows' number of elements, each set to 0.0f
    rowSum.assign(currentRows, 0.0f);
    colSum.assign(currentColumns, 0.0f);

    // calculate sum over rows and columns
    for (int32_t row{ 0 }; row < currentRows; ++row)
    {
        for (int32_t col{ 0 }; col < currentColumns; ++col)
        {
            // Add the value at the current data[row][col] to rowSum at index 'row',
            // effectively summing all elements in this row
            rowSum[row] += data[row][col];
            colSum[col] += data[row][col];
        }
    }
}

void Excel::drawGraphButton()
{
    if (ImGui::Button("show graph", ImVec2(100, 30)))
    {
        graphVisible = true;
    }
}

void Excel::drawGraph()
{
    if (graphVisible)
    {
        if (!data.empty() && !data[0].empty())
        {
            ImGui::Begin("graph", &graphVisible);
            ImGui::Text("sum");

            vector<float> totalColSum;
            totalColSum.reserve(data[0].size());
            // iterate to find total column sum
            for (size_t col{ 0 }; col < data[0].size(); ++col)
            {
                float colSum = 0.0f;
                for (size_t row{ 0 }; row < data.size(); ++row)
                {
                    colSum += data[row][col];
                }
                totalColSum.push_back(colSum);
            }

            ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(1.0f, 0.647f, 0.0f, 1.f));
            ImGui::PlotLines("", totalColSum.data(), totalColSum.size(), 0, "", FLT_MAX, FLT_MAX, ImVec2(800, 400));
            ImGui::PopStyleColor();

            ImGui::End();

        }
        else
        {
            graphVisible = false;
        }
    }
}

void Excel::openSaveButtons()
{
    ImGui::Separator();
    if (ImGui::Button("save", ImVec2(200, 30)))
    {
        ImGui::OpenPopup("save file");
    }
    ImGui::SameLine();
    //ImGui::Separator();
    if (ImGui::Button("load", ImVec2(200, 30)))
    {
        ImGui::OpenPopup("load file");
    }
    //ImGui::Separator();
    ImGui::SameLine();
    if (ImGui::Button("clear", ImVec2(200, 30)))
    {
        data.clear();
        currentRows = 0;
        currentColumns = 0;
    }
    savePopup();
    loadPopup();
}

void Excel::savePopup()
{
    setPopupLayout();
    if (ImGui::BeginPopupModal("save file", NULL, popupFlags))
    {
        ImGui::Text("enter file name: ");
        ImGui::InputText("##filename", fileNameBuffer, sizeof(fileNameBuffer));

        if (ImGui::Button("save"))
        {
            saveFile(fileNameBuffer);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();

    }
}

void Excel::saveFile(string fileName)
{
    auto output = ofstream{ fileName.data() };
    if (!output.is_open())
    {
        return;
    }
    //
    for (int32_t row{ 0 }; row < currentRows; row++)
    {
        for (int32_t col{ 0 }; col < currentColumns; col++)
        {
            output << data[row][col];
            output << ',';
        }
        output << endl; 
    }
    output.close();
}

void Excel::loadPopup()
{
    setPopupLayout();
    if (ImGui::BeginPopupModal("load file", NULL, popupFlags))
    {
        ImGui::Text("enter file name: ");
        ImGui::InputText("##filename", fileNameBuffer, sizeof(fileNameBuffer));

        if (ImGui::Button("load"))
        {
            loadFile(fileNameBuffer);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();

    }
}

void Excel::loadFile(string filename)
{
    // Open the file using the name provided by `filename`
    auto inputFile = ifstream{ filename.data() };
    if (!inputFile.is_open())
    {
        return;
    }
    // Clear any existing data that might be in the `data` container.
    data.clear();
    // Declare a string to hold each line read from the file.
    string line = string{};
    unsigned int numOfRows{ 0U };
    // Read the file line by line using getline.
    while (getline(inputFile, line))
    {
        // Use a string stream to read comma-separated values from the line
        auto streamString = istringstream(line);
        vector<float> row{};
        string value;
        // Read each comma-separated value into the value string
        while (getline(streamString, value, ','))
        {
            // Convert the value string to float and add it to the row vector
            row.push_back(stof(value));
        }
        data.push_back(row);
        ++numOfRows;
    }
    inputFile.close();
    currentRows = numOfRows;

    if (currentRows > 0U)
    {
        // If so, set currentColumns to the size of the first row (assuming all rows have the same number of columns)
        currentColumns = (data[0].size());
    }
    else
    {
        currentColumns = 0;
    }
}

void Excel::setImGuiStyleColors()
{
    ImGuiStyle& style = ImGui::GetStyle();

    ImVec4 whiteGreyColor = ImVec4(0.82f, 0.82f, 0.82f, 1.0f);
    ImVec4 normalColor = ImVec4(0.0f, 0.8f, 0.4f, 1.0f);
    ImVec4 hovered = ImVec4(0.19f, 0.87f, 0.59f, 1.0f);
    ImVec4 clicked = ImVec4(0.02f, 0.98f, 0.58f, 1.0f);

    // change text colors to black
    //style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    //style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}
