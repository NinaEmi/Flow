#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <limits>
#include <functional>
#include <sstream>
#include <unordered_map>

using namespace std;

struct FileContent
{
    string content;
    string description;
};

struct CSVData
{
    vector<vector <string> > data;
    string description;
};

// Clasa de excepție pentru numere întregi invalide
class InvalidIntegerInputException : public std::exception
{
public:
    const char *what() const throw() override
    {
        return "Invalid input. Please enter a valid integer.";
    }
};

// Clasa de excepție pentru numere float invalide
class InvalidFloatInputException : public std::exception
{
public:
    const char *what() const throw() override
    {
        return "Invalid input. Please enter a valid number.";
    }
};

// Clasa de baza abstracta pentru pasi
class Step
{
public:
    virtual void displayInfo() const = 0; // Metoda virtuala pura pentru afisarea informatiilor despre pas
    void execute() const;

    virtual ~Step(){};
};

template <typename T>
void performOperation(const T &numberInput, const T &calculusStep, const string &operationStr)
{
    if (operationStr == "+")
    {
        cout << "Result = " << (numberInput + calculusStep) << endl;
    }
    else if (operationStr == "-")
    {
        cout << "Result = " << (numberInput - calculusStep) << endl;
    }
    else if (operationStr == "*")
    {
        cout << "Result = " << (numberInput * calculusStep) << endl;
    }
    else if (operationStr == "/")
    {
        if (calculusStep == 0)
        {
            cout << "Error! Division by 0! " << endl;
        }
        else
        {
            cout << "Result = " << (numberInput / calculusStep) << endl;
        }
    }
    else if (operationStr == "max")
    {
        cout << "Result = " << max(numberInput, calculusStep) << endl;
    }
    else if (operationStr == "min")
    {
        cout << "Result = " << min(numberInput, calculusStep) << endl;
    }

    else
    {
        cout << "Invalid operation!" << endl;
    }
}

// Clasa pentru pasul de tip TITLE
class TitleStep : public Step
{
private:
    string title;
    string subtitle;

public:
    TitleStep(const string &title, const string &subtitle)
        : title(title), subtitle(subtitle) {}

    void displayInfo() const override
    {
        cout << "Title Step - Title: " << title << ", Subtitle: " << subtitle << endl;
    }

    string getTitle()
    {
        return this->title;
    }

    void setTitle(string title)
    {
        this->title = title;
    }

    string getSubtitle()
    {
        return this->subtitle;
    }

    void setSubtitle(string subtitle)
    {
        this->subtitle = subtitle;
    }
};

// Clasa pentru pasul de tip TEXT
class TextStep : public Step
{
private:
    string title;
    string copy;

public:
    TextStep(const string &title, const string &copy)
        : title(title), copy(copy) {}

    void displayInfo() const override
    {
        cout << "Text Step - Title: " << title << ", Copy: " << copy << endl;
    }

    string getTitle()
    {
        return this->title;
    }

    void setTitle(string title)
    {
        this->title = title;
    }

    string getCopy()
    {
        return this->copy;
    }

    void setCopy(string copy)
    {
        this->copy = copy;
    }
};

// Clasa pentru pasul de tip Text Input
class TextInput : public Step
{
private:
    string description;
    string textInput;

public:
    string getDescription()
    {
        return this->description;
    }

    void setDescription(string description)
    {
        this->description = description;
    }

    string getTextInput()
    {
        return this->textInput;
    }

    void setTextInput(string textInput)
    {
        this->textInput = textInput;
    }

    TextInput(const string &description, const string &textInput) : description(description), textInput(textInput) {}

    void displayInfo() const override
    {
        cout << "Text Input Step - Description: " << description << ", Text Input: " << textInput << endl;
    }
};

// Clasa pentru pasul de tip Number Input
class NumberInput : public Step
{
private:
    string description;
    int numberInput;

public:
    NumberInput(const string &description, const float numberInput) : description(description), numberInput(numberInput) {}

    void displayInfo() const override
    {
        cout << "Number Input Step - Description: " << description << ", Number Input: " << numberInput << endl;
    }

    string getDescription()
    {
        return this->description;
    }

    void setDescription(string description)
    {
        this->description = description;
    }

    float getNumberInput()
    {
        return this->numberInput;
    }

    void setNumberInput(float numberInput)
    {
        this->numberInput = numberInput;
    }
};

// Clasa pentru pasul de tip Calculus Step
class CalculusStep : public Step
{
private:
    int steps;
    string operation;

public:
    CalculusStep(int steps, const string &operation)
        : steps(steps), operation(operation) {}

    void displayInfo() const override
    {
        cout << "Calculus Step - Steps: " << steps << ", Operation: " << operation << endl;
    }

    int getSteps()
    {
        return this->steps;
    }

    void setSteps(int steps)
    {
        this->steps = steps;
    }

    string getOperation()
    {
        return this->operation;
    }

    void setOperation(string operation)
    {
        this->operation = operation;
    }
};

// Clasa pentru pasul de tip Display Step
class DisplayStep : public Step
{
private:
    int step;

public:
    DisplayStep(int step)
        : step(step) {}

    void displayInfo() const override
    {
        cout << "DISPLAY Step - Step: " << step << endl;
    }

    int getStep()
    {
        return this->step;
    }

    void setStep(int step)
    {
        this->step = step;
    }
};

// Clasa pentru pasul de tip Text File Input
class TextFileInputStep : public Step
{
private:
    string description;
    string file_name;

public:
    TextFileInputStep(const string &desc, const string &file)
        : description(desc), file_name(file) {}

    void displayInfo() const override
    {
        cout << "TEXT FILE Input Step - Description: " << description << ", File Name: " << file_name << endl;
    }

    string getDescription()
    {
        return this->description;
    }

    void setDescription(string description)
    {
        this->description = description;
    }

    string getFile_name()
    {
        return this->file_name;
    }

    void setFile_name(string file_name)
    {
        this->file_name = file_name;
    }
};

// Clasa pentru pasul de tipul Csv File
class CSVFileInputStep : public Step
{
private:
    string description;
    string file_name;

public:
    CSVFileInputStep(const string &desc, const string &file)
        : description(desc), file_name(file) {}

    void displayInfo() const override
    {
        cout << "CSV FILE Input Step - Description: " << description << ", File Name: " << file_name << endl;
    }

    string getDescription()
    {
        return this->description;
    }

    void setDescription(string description)
    {
        this->description = description;
    }

    string getFile_name()
    {
        return this->file_name;
    }

    void setFile_name(string file_name)
    {
        this->file_name = file_name;
    }
};
class Flow
{
private:
    string flowTitle;
    vector<Step *> steps; // Vector pentru a stoca pasii
    vector<FileContent> fileContents;

public:
    Flow(const string &title) : flowTitle(title) {}

    string getFlowTitle() const
    {
        return flowTitle;
    }

    void addStep(Step *step)
    {
        steps.push_back(step);
    }

    void displayStepsInfo() const
    {
        for (const auto &step : steps)
        {
            step->displayInfo();
        }
    }

    size_t getStepsCount() const
    {
        return steps.size();
    }

    Step *getStep(size_t index) const
    {
        if (index < steps.size())
        {
            return steps[index];
        }
        return nullptr;
    }

    const vector<Step *> &getSteps() const
    {
        return steps;
    }

    vector<NumberInput *> getNumberInputSteps() const
    {
        vector<NumberInput *> numberInputSteps;

        for (Step *step : steps)
        {
            if (NumberInput *numberInput = dynamic_cast<NumberInput *>(step))
            {
                numberInputSteps.push_back(numberInput);
            }
        }

        return numberInputSteps;
    }
    void addFileContent(const FileContent &fileContent)
    {
        fileContents.push_back(fileContent);
    }

    const vector<FileContent> &getFileContents() const
    {
        return fileContents;
    }

    /* ~Flow()
     {
         // Eliberarea memoriei pentru fiecare obiect Step
         for (Step *step : steps)
         {
             delete step;
         }
     }*/
};

// Clasa pentru tipul Output Step
class OutputStep : public Step
{
private:
    int step;
    string file_name;
    string title;
    string description;

public:
    OutputStep(int step, const string &file, const string &title, const string &desc)
        : step(step), file_name(file), title(title), description(desc) {}

    void displayInfo() const override
    {
        cout << "OUTPUT Step - Step: " << step << ", File Name: " << file_name
             << ", Title: " << title << ", Description: " << description << endl;
    }

    int getStep()
    {
        return this->step;
    }

    void setStep(int step)
    {
        this->step = step;
    }

    string getFile_name()
    {
        return this->file_name;
    }

    void setFile_name(string file_name)
    {
        this->file_name = file_name;
    }

    string getTitle()
    {
        return this->title;
    }

    void setTitle(string title)
    {
        this->title = title;
    }

    string getDescription()
    {
        return this->description;
    }

    void setDescription(string description)
    {
        this->description = description;
    }
};

class EndStep : public Step
{
private:
    string endStep;

public:
    EndStep(const string &endStep) : endStep(endStep) {}

    void displayInfo() const override
    {
        cout << endStep << endl;
    }

    string getEndStep()
    {
        return this->endStep;
    }

    void setEndStep(string endStep)
    {
        this->endStep = endStep;
    }
};

// Clasa pentru gestionarea fluxului

void writeFlowToFile(const Flow &flow, const string &filename)
{
    ofstream file(filename, ios::app);

    if (file.is_open())
    {
        file << "Flow Title: " << flow.getFlowTitle() << endl;
        const vector<Step *> &steps = flow.getSteps();
        for (const auto &step : steps)
        {
            // Utilizăm un dynamic_cast pentru a identifica tipul fiecărui pas și a scrie informațiile relevante în fișier
            if (dynamic_cast<TitleStep *>(step))
            {
                TitleStep *titleStep = dynamic_cast<TitleStep *>(step);
                file << "Title Step - Title: " << titleStep->getTitle() << ", Subtitle: " << titleStep->getSubtitle() << endl;
            }
            if (dynamic_cast<TextStep *>(step))
            {
                TextStep *textStep = dynamic_cast<TextStep *>(step);
                file << "Text Step - Title: " << textStep->getTitle() << ", Copy: " << textStep->getCopy() << endl;
            }
            if (dynamic_cast<TextInput *>(step))
            {
                TextInput *textInputStep = dynamic_cast<TextInput *>(step);
                file << "Text Input Step - Description: " << textInputStep->getDescription() << ", Text Input: " << textInputStep->getTextInput() << endl;
            }
            if (dynamic_cast<NumberInput *>(step))
            {
                NumberInput *numberInputStep = dynamic_cast<NumberInput *>(step);
                file << "Number Input Step - Description: " << numberInputStep->getDescription() << ", Number Input: " << numberInputStep->getNumberInput() << endl;
            }
            if (dynamic_cast<CalculusStep *>(step))
            {
                CalculusStep *calculusStep = dynamic_cast<CalculusStep *>(step);
                file << "Calculus Step - Steps: " << calculusStep->getSteps() << ", Operation: " << calculusStep->getOperation() << endl;
            }
            if (dynamic_cast<DisplayStep *>(step))
            {
                DisplayStep *displayStep = dynamic_cast<DisplayStep *>(step);
                file << "DISPLAY Step - Step: " << displayStep->getStep() << endl;
            }
            if (dynamic_cast<TextFileInputStep *>(step))
            {
                TextFileInputStep *textFileInputStep = dynamic_cast<TextFileInputStep *>(step);
                file << "TEXT FILE Input Step - Description: " << textFileInputStep->getDescription() << ", File Name: " << textFileInputStep->getFile_name() << endl;
            }
            if (dynamic_cast<CSVFileInputStep *>(step))
            {
                CSVFileInputStep *csvFileInputStep = dynamic_cast<CSVFileInputStep *>(step);
                file << "CSV FILE Input Step - Description: " << csvFileInputStep->getDescription() << ", File Name: " << csvFileInputStep->getFile_name() << endl;
            }
            if (dynamic_cast<OutputStep *>(step))
            {
                OutputStep *outputStep = dynamic_cast<OutputStep *>(step);
                file << "OUTPUT Step - Step: " << outputStep->getStep() << ", File Name: " << outputStep->getFile_name()
                     << ", Title: " << outputStep->getTitle() << ", Description: " << outputStep->getDescription() << endl;
            }
            if (dynamic_cast<EndStep *>(step))
            {
                EndStep *endStep = dynamic_cast<EndStep *>(step);
                file << endStep->getEndStep() << endl;
            }
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }
}

// Funcție pentru verificarea unei intrări int
int validateIntegerInput(const string &prompt, int &contor)
{
    int input;
    bool validInput = false;

    do
    {
        cout << prompt;
        if (!(cin >> input))
        {
            contor++; // Incrementarea contorului pentru mesajele de eroare

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Curățăm bufferul
            cout << "Invalid input. Please enter a valid number." << endl;

            char choice;
            cout << "Do you want to try again? (Y/N): ";
            cin >> choice;
            cin.ignore();
            if (toupper(choice) != 'Y')
            {
                // În caz că utilizatorul nu dorește să continue, se returnează o valoare invalidă
                return numeric_limits<float>::quiet_NaN();
            }
        }
        else
        {
            cin.ignore();
            validInput = true; // În caz că intrarea este validă, ieșim din buclă
        }
    } while (!validInput);

    return input;
}

bool containsAlphanumeric(const string &input)
{
    for (char c : input)
    {
        if (!isalnum(c) && c != ' ')
        {
            return false; // Return false if we find a non-alphanumeric character (excluding space)
        }
    }
    return true;
}

string validateStringInput(const string &prompt, int &contor)
{
    string input;
    bool validInput = false;

    do
    {
        cout << prompt;
        getline(cin, input);

        if (input.empty() || !containsAlphanumeric(input))
        {
            cout << "Invalid input. Please enter a valid string." << endl;

            contor++; // Incrementarea contorului pentru mesajele de eroare

            char choice;
            cout << "Do you want to try again? (Y/N): ";
            cin >> choice;
            cin.ignore();

            if (toupper(choice) != 'Y')
            {
                // În caz că utilizatorul nu dorește să continue, se returnează un șir vid (poate fi tratat mai departe în cod)
                return "";
            }
        }
        else
        {
            validInput = true; // În caz că intrarea este validă, ieșim din buclă
        }
    } while (!validInput);

    return input;
}

vector<Flow> readFlowsFromFile(const string &filename)
{
    vector<Flow> flows;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        string currentFlowTitle;
        bool isReadingFlow = false;
        Flow currentFlow("temp");

        while (getline(file, line))
        {
            if (line.substr(0, 11) == "Flow Title:")
            {
                if (isReadingFlow)
                {
                    flows.push_back(currentFlow);
                    currentFlow = Flow("temp");
                }
                currentFlowTitle = line.substr(12);
                currentFlow = Flow(currentFlowTitle);
                isReadingFlow = true;
            }
            else
            {
                // Verificăm tipul de pas și extragem informațiile corespunzătoare
                if (line.find("Title Step") != string::npos)
                {
                    // Identificăm și extragem informațiile pentru pasul de tip Title Step
                    string titleInfo = line.substr(line.find("Title: ") + 7);
                    string title = titleInfo.substr(0, titleInfo.find(", Subtitle: "));
                    string subtitle = titleInfo.substr(titleInfo.find("Subtitle: ") + 10);

                    // Creăm obiectul TitleStep și îl adăugăm la fluxul curent
                    TitleStep *titleStep = new TitleStep(title, subtitle);
                    currentFlow.addStep(titleStep);
                }
                else if (line.find("Text Step") != string::npos)
                {
                    string textInfo = line.substr(line.find("Title: ") + 7);
                    string text = textInfo.substr(0, textInfo.find(", Copy: "));
                    string copy = textInfo.substr(textInfo.find("Copy: ") + 6);

                    TextStep *textStep = new TextStep(text, copy);
                    currentFlow.addStep(textStep);
                }

                else if (line.find("Text Input") != string::npos)
                {
                    string textInputInfo = line.substr(line.find("Description: ") + 13);
                    string description = textInputInfo.substr(0, textInputInfo.find(", Text Input: "));
                    string textInput = textInputInfo.substr(textInputInfo.find("Text Input: ") + 12);

                    TextInput *textInputStep = new TextInput(description, textInput);
                    currentFlow.addStep(textInputStep);
                }
                else if (line.find("Number Input") != string::npos)
                {
                    string numberInputInfo = line.substr(line.find("Description: ") + 13);

                    string description = numberInputInfo.substr(0, numberInputInfo.find(", Number Input: "));
                    int numberInput = stoi(numberInputInfo.substr(numberInputInfo.find("Number Input: ") + 14));

                    NumberInput *numberInputStep = new NumberInput(description, numberInput);
                    currentFlow.addStep(numberInputStep);
                }
                else if (line.find("Calculus Step") != string::npos)
                {
                    string calculusInfo = line.substr(line.find("Steps: ") + 7);
                    int steps = stoi(calculusInfo.substr(0, calculusInfo.find(", Operation: ")));
                    string operation = calculusInfo.substr(calculusInfo.find("Operation: ") + 11);

                    CalculusStep *calculusStep = new CalculusStep(steps, operation);
                    currentFlow.addStep(calculusStep);
                }
                else if (line.find("DISPLAY") != string::npos)
                {
                    string displayInfo = line.substr(line.find("Step: ") + 6);
                    int steps = stoi(displayInfo);

                    DisplayStep *displayStep = new DisplayStep(steps);
                    currentFlow.addStep(displayStep);
                }
                else if (line.find("TEXT FILE") != string::npos)
                {
                    string textFile = line.substr(line.find("Description: ") + 13);
                    string description = textFile.substr(0, textFile.find(", File Name: "));
                    string fileName = textFile.substr(textFile.find("File Name: ") + 11);

                    TextFileInputStep *textFileStep = new TextFileInputStep(description, fileName);
                    currentFlow.addStep(textFileStep);
                }
                else if (line.find("CSV FILE") != string::npos)
                {
                    string csvFile = line.substr(line.find("Description: ") + 13);
                    string description = csvFile.substr(0, csvFile.find(", File Name: "));
                    string fileName = csvFile.substr(csvFile.find("File Name: ") + 11);

                    CSVFileInputStep *csvFileStep = new CSVFileInputStep(description, fileName);
                    currentFlow.addStep(csvFileStep);
                }
                else if (line.find("OUTPUT Step") != string::npos)
                {
                    size_t stepPosition = line.find("Step: ");
                    size_t filePosition = line.find("File Name: ");
                    size_t titlePosition = line.find("Title: ");
                    size_t descriptionPosition = line.find("Description: ");

                    int steps = stoi(line.substr(stepPosition + 6, filePosition - (stepPosition + 8)));
                    string fileName = line.substr(filePosition + 11, titlePosition - (filePosition + 13));
                    string title = line.substr(titlePosition + 7, descriptionPosition - (titlePosition + 9));
                    string description = line.substr(descriptionPosition + 13);

                    OutputStep *outputStep = new OutputStep(steps, fileName, title, description);
                    currentFlow.addStep(outputStep);
                }
            }
        }

        // Adăugăm ultimul flux citit în vectorul de fluxuri
        if (isReadingFlow)
        {
            flows.push_back(currentFlow);
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file!" << endl;
    }

    return flows;
}

int runFlow(const Flow &flow)
{
    cout << "Running flow: " << flow.getFlowTitle() << endl;

    int currentStepIndex = 0;
    int contor = 0;

    while (currentStepIndex < flow.getSteps().size())
    {
        Step *currentStep = flow.getSteps()[currentStepIndex];

        char choice;
        cout << "Press 'n' for next step, 's' to skip: ";
        cin >> choice;
        cin.ignore(); // Ignoră newline-ul din buffer

        if (toupper(choice) == 'S')
        {
            cout << "Skipping to next step..." << endl;
            currentStepIndex++; // Sarim peste acest pas
            contor++;
            continue;
        }
        else if (toupper(choice) != 'N')
        {
            cout << "Invalid choice! Moving to next step." << endl;
            continue;
        }

        currentStep->displayInfo();

        currentStepIndex++;
    }

    return contor;
}

void deleteFlowFromFile(const string &filename, const string &flowTitleToDelete)
{
    vector<Flow> flows = readFlowsFromFile(filename);
    bool found = false;

    for (auto it = flows.begin(); it != flows.end(); ++it)
    {
        if (it->getFlowTitle() == flowTitleToDelete)
        {
            flows.erase(it); // Ștergem fluxul din vector
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Flow not found!" << endl;
        return;
    }

    ofstream rewriteFile("temp.txt");

    if (rewriteFile.is_open())
    {
        for (const Flow &flow : flows)
        {
            if (flow.getFlowTitle() != flowTitleToDelete)
            {
                rewriteFile << "Flow Title: " << flow.getFlowTitle() << endl;
                for (const auto &step : flow.getSteps())
                {
                    if (auto *titleStep = dynamic_cast<TitleStep *>(step))
                    {
                        rewriteFile << "Title Step - Title: " << titleStep->getTitle() << ", Subtitle: " << titleStep->getSubtitle() << endl;
                    }
                    else if (auto *textStep = dynamic_cast<TextStep *>(step))
                    {
                        rewriteFile << "Text Step - Title: " << textStep->getTitle() << ", Copy: " << textStep->getCopy() << endl;
                    }
                    // TODO: Adaugă condiții pentru celelalte tipuri de pași, similar cu cum ai făcut în funcția de scriere în fișier
                }
            }
        }

        rewriteFile.close();

        // Șterge fișierul vechi și redenumește fișierul nou
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        cout << "Flow deleted successfully!" << endl;
    }
    else
    {
        cout << "Unable to rewrite the file!" << endl;
    }
}

bool askForContinue()
{
    char choice;
    cout << endl;
    cout << "Do you want to continue? (Y/N): ";
    cin >> choice;
    cin.ignore();
    return (toupper(choice) == 'Y');
}

bool titleExists(const string &filename, const string &newTitle)
{
    ifstream file(filename);
    string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            if (line.find("Flow Title: ") != string::npos)
            {
                size_t titlePos = line.find("Flow Title: ");
                if (titlePos != string::npos)
                {
                    string extractedTitle = line.substr(titlePos + 12);
                    if (extractedTitle == newTitle)
                    {
                        file.close();
                        return true;
                    }
                }
            }
        }
        file.close();
    }

    return false;
}

bool hasTxtExtension(const string &fileName)
{
    size_t pos = fileName.find_last_of(".");
    if (pos != string::npos)
    {
        string extension = fileName.substr(pos + 1);
        return (extension == "txt");
    }
    return false;
}

bool hasCsvExtension(const string &fileName)
{
    size_t pos = fileName.find_last_of(".");
    if (pos != string::npos)
    {
        string extension = fileName.substr(pos + 1);
        return (extension == "csv");
    }
    return false;
}

int chooseFileToDisplay(const vector<FileContent> &fileContents)
{
    cout << "Choose a file to display:" << endl;
    for (size_t i = 0; i < fileContents.size(); ++i)
    {
        cout << i + 1 << ". " << fileContents[i].description << endl;
    }

    int choice;
    do
    {
        cout << "Enter your choice (1-" << fileContents.size() << "): ";
        if (!(cin >> choice) || choice < 1 || choice > static_cast<int>(fileContents.size()))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a valid number." << endl;
        }
        else
        {
            cin.ignore(); // Consumăm newline-ul lăsat de cin >> choice
            break;
        }
    } while (true);

    return choice - 1;
}

FileContent uploadFile(const string &filePath)
{
    ifstream file(filePath);
    FileContent fileContent;

    int errorCount = 0;
    if (file.is_open())
    {
        cout << "File opened successfully!" << endl;

        // Salvează conținutul fișierului într-un string
        stringstream buffer;
        buffer << file.rdbuf();
        fileContent.content = buffer.str();

        fileContent.description = validateStringInput("Enter File Description: ", errorCount);

        file.close();
    }
    else
    {
        cout << "Failed to open file!" << endl;
    }
    return fileContent;
}

CSVData uploadCSVFile(const string &filePath)
{
    ifstream file(filePath);
    CSVData csvData;
    int errorCount = 0;

    if (file.is_open())
    {
        cout << "File opened successfully!" << endl;

        // Salvează conținutul fișierului CSV într-un vector bidimensional
        vector<vector <string> > table;
        string line;

        while (getline(file, line))
        {
            istringstream iss(line);
            vector<string> row;

            string field;
            while (getline(iss, field, ','))
            {
                row.push_back(field);
            }

            table.push_back(row);
        }

        csvData.data = table;

        csvData.description = validateStringInput("Enter CSV File Description: ", errorCount);

        file.close();
    }
    else
    {
        cout << "Failed to open file!" << endl;
    }

    return csvData;
}

int main()
{
    Flow myFlow("TITLE");

    myFlow.displayStepsInfo();
    string filename = "flow.txt";
    unordered_map<string, int> flowRuns; // Mapare între numele flow-ului și numărul de rulări
    int errorCount = 0;
    int errorCountInt = 0;

    cout << "-------WELCOME-------" << endl
         << "----MENU----" << endl;

    int choice;

    cout << "Enter your choice: " << endl;

    cout << "1. Create a flow. " << endl;
    cout << "2. Run a flow. " << endl;
    cout << "3. Delete a flow. " << endl;

    do
    {
        do
        {
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                cin.ignore();
                string flowTitle;
                cout << "Enter the name of the flow: ";
                getline(cin, flowTitle);

                if (titleExists(filename, flowTitle))
                {
                    cout << "Flow already exists!" << endl;
                }
                else
                {
                    Flow myFlow(flowTitle);

                    string title, subtitle, textTitle, textCopy, textInputDescription, textInput, numberInputDescription, operation,
                        nameFile, csvFileDescription, titleOutput, csvFileName, textFileDescription, textFileName, descriptionOutput;

                    int calculusStep, outputStep;
                    float numberInput;
                    bool done = false;

                    while (done == false)
                    {
                        cout << "Choose the type of step to add:" << endl;
                        cout << "1. TITLE step: title (string), subtitle (string)" << endl;
                        cout << "2. TEXT step: title (string), copy (string)" << endl;
                        cout << "3. TEXT INPUT step: description (string), text input (string)" << endl;
                        cout << "4. NUMBER INPUT step: description (string), number input (float)" << endl;
                        cout << "5. CALCULUS step: steps (integer), operation (string)" << endl;
                        cout << "6. DISPLAY steps: step (integer)" << endl;
                        cout << "7. TEXT FILE input step: description, file_name " << endl;
                        cout << "8. CSV FILE input step: description, file_name" << endl;
                        cout << "9.OUTPUT step: step (integer), name of file (string), title (text), description (text)" << endl;
                        cout << "10.END step" << endl;

                        int choice1;
                        cin >> choice1;
                        cin.ignore();
                        try
                        {
                            switch (choice1)
                            {
                            case 1:
                            {
                                title = validateStringInput("Enter Title: ", errorCount);
                                subtitle = validateStringInput("Enter Subtitle: ", errorCount);

                                if (!title.empty() && !subtitle.empty())
                                {

                                    myFlow.addStep(new TitleStep(title, subtitle));
                                }
                                else
                                {
                                    cout << "Skipping this step due to invalid input." << endl;
                                }
                                break;
                            }
                            case 2:
                            {
                                textTitle = validateStringInput("Enter Text Title: ", errorCount);
                                textCopy = validateStringInput("Enter Text Copy: ", errorCount);

                                if (!textTitle.empty() && !textCopy.empty())
                                {

                                    myFlow.addStep(new TextStep(textTitle, textCopy));
                                }
                                else
                                {
                                    cout << "Skipping this step due to invalid input." << endl;
                                }
                                break;
                            }
                            case 3:
                            {
                                textInputDescription = validateStringInput("Enter Text Input Description: ", errorCount);
                                textInput = validateStringInput("Enter Text Input: ", errorCount);

                                if (!textInput.empty() && !textInputDescription.empty()) // Verificăm dacă ambele intrări sunt valide
                                {
                                    myFlow.addStep(new TextInput(textInputDescription, textInput));
                                }
                                else
                                {
                                    cout << "Skipping this step due to invalid input." << endl;
                                }
                                break;
                            }
                            case 4:
                            {
                                int numberOfInputs;
                                numberInputDescription = validateStringInput("Enter Number Input Description: ", errorCount);

                                numberOfInputs = validateIntegerInput("Enter the number of inputs: ", errorCount);

                                // Verificare dacă numărul de intrări este valid
                                if (numberOfInputs <= 0)
                                {
                                    cout << "Invalid number of inputs. Exiting program." << endl;
                                    return 1;
                                }

                                // Buclă pentru a solicita intrări multiple
                                for (int i = 0; i < numberOfInputs; ++i)
                                {
                                    int numberInput = validateIntegerInput("Enter Number Input: ", errorCount);

                                    if (!isnan(numberInput) && !numberInputDescription.empty())
                                    {
                                        myFlow.addStep(new NumberInput(numberInputDescription, numberInput));
                                    }
                                    else
                                    {
                                        cout << "Skipping this step due to invalid input." << endl;
                                    }
                                    cout << endl;
                                }
                                break;
                            }

                            case 5:
                            {
                                // Verificăm dacă există pași de tip NumberInput în flux
                                vector<NumberInput *> numberInputSteps = myFlow.getNumberInputSteps();
                                if (numberInputSteps.empty())
                                {
                                    cout << "No Number Input steps available. Please add Number Input steps first." << endl;
                                    break;
                                }

                                // Afișăm toți pașii Number Input disponibili
                                cout << "Available Number Input Steps:" << endl;
                                for (size_t i = 0; i < numberInputSteps.size(); ++i)
                                {
                                    cout << i + 1 << ". " << numberInputSteps[i]->getNumberInput() << endl;
                                }

                                // Utilizatorul alege două numere din pașii disponibili
                                size_t selectedStepIndex1, selectedStepIndex2;
                                do
                                {
                                    cout << "Choose the first step (1-" << numberInputSteps.size() << "): ";
                                    if (!(cin >> selectedStepIndex1) || selectedStepIndex1 < 1 || selectedStepIndex1 > numberInputSteps.size())
                                    {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Invalid choice. Please enter a valid number." << endl;

                                        errorCountInt++;

                                        char choice;
                                        cout << "Do you want to try again? (Y/N): ";
                                        cin >> choice;
                                        cin.ignore();
                                        if (toupper(choice) != 'Y')
                                        {
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cin.ignore();
                                        break;
                                    }
                                } while (true);

                                do
                                {
                                    cout << "Choose the second step (1-" << numberInputSteps.size() << "): ";
                                    if (!(cin >> selectedStepIndex2) || selectedStepIndex2 < 1 || selectedStepIndex2 > numberInputSteps.size())
                                    {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Invalid choice. Please enter a valid number." << endl;
                                        errorCountInt ++;

                                        char choice;
                                        cout << "Do you want to try again? (Y/N): ";
                                        cin >> choice;
                                        cin.ignore();
                                        if (toupper(choice) != 'Y')
                                        {
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cin.ignore();
                                        break;
                                    }
                                } while (true);

                                // Utilizatorul alege operația
                                string operation;
                                cout << "Enter Calculus Operation: ";
                                getline(cin, operation);

                                // Efectuăm operația
                                performOperation(numberInputSteps[selectedStepIndex1 - 1]->getNumberInput(),
                                                 numberInputSteps[selectedStepIndex2 - 1]->getNumberInput(),
                                                 operation);

                                break;
                            }

                            case 6:
                            {
                                if (myFlow.getFileContents().empty())
                                {
                                    cout << "No files available for display." << endl;
                                    break;
                                }

                                int fileIndex = chooseFileToDisplay(myFlow.getFileContents());
                                const FileContent &chosenFile = myFlow.getFileContents()[fileIndex];

                                if (hasCsvExtension(chosenFile.description))
                                {
                                    // Afișează conținutul pentru fișierele CSV
                                    cout << "CSV File Content:\n";
                                }
                                else
                                {
                                    // Afișează conținutul pentru celelalte tipuri de fișiere
                                    cout << "File Content:\n"
                                         << chosenFile.content << endl;
                                }
                                break;
                            }

                            case 7:
                            {
                                string filePath;

                                do
                                {
                                    cout << "Enter the path of the file to upload: ";
                                    getline(cin, filePath);
                                    FileContent fileContent = uploadFile(filePath);

                                    if (!hasTxtExtension(filePath))
                                    {
                                        cout << "The file does not have a .txt extension." << endl;
                                        errorCountInt ++;

                                        char choice;
                                        cout << "Do you want to try again? (Y/N): ";
                                        cin >> choice;
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                        if (toupper(choice) != 'Y')
                                        {
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        myFlow.addFileContent(fileContent);
                                        myFlow.addStep(new TextFileInputStep(textFileDescription, filePath));
                                        cin.ignore();
                                        break;
                                    }

                                } while (true);

                                break;
                            }
                            case 8:
                            {
                                string csvFilePath;

                                do
                                {
                                    cout << "Enter the path of the CSV file: ";
                                    getline(cin, csvFilePath);

                                    FileContent fileContent = uploadFile(csvFilePath);

                                    if (!hasCsvExtension(csvFilePath))
                                    {
                                        cout << "The file does not have a .csv extension." << endl;
                                        errorCountInt ++;

                                        char choice;
                                        cout << "Do you want to try again? (Y/N): ";
                                        cin >> choice;
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                        if (toupper(choice) != 'Y')
                                        {
                                            break; // Exit the loop if the user chooses not to try again
                                        }
                                    }
                                    else
                                    {
                                        myFlow.addFileContent(fileContent);
                                        myFlow.addStep(new CSVFileInputStep(csvFileDescription, csvFilePath));
                                        cin.ignore();
                                        break;
                                    }
                                } while (true);
                                break;
                            }
                            case 9:
                            {
                                const vector<Step *> &steps = myFlow.getSteps();
                                cout << "Enter Name of File you want to generate: ";
                                getline(cin, nameFile);
                                cout << "Enter Title of File you want to generate: ";
                                getline(cin, titleOutput);
                                cout <<"Enter a Description ";
                                getline(cin, descriptionOutput);

                                ofstream file(nameFile + ".txt", ios::app); // Deschide în modul append

                                if (!file.is_open())
                                {
                                    cout << "Error: Unable to open the file for writing." << endl;
                                    break;
                                }

                                while (true)
                                {
                                    // Afișează toți pașii cu un index
                                    for (size_t i = 0; i < steps.size(); i++)
                                    {
                                        cout << i + 1 << ". ";
                                        steps[i]->displayInfo(); // Presupunând că fiecare pas are o metodă displayInfo()
                                    }

                                    cout << "Enter the index of the step you want to add to the file: ";
                                    int index;
                                    cin >> index;
                                    cin.ignore();

                                    if (index > 0 && index <= static_cast<int>(steps.size()))
                                    {
                                        int idx = index - 1;
                                        if (TitleStep *titleStep = dynamic_cast<TitleStep *>(steps[idx]))
                                        {
                                            file << "Title Step - Title: " << titleStep->getTitle() << ", Subtitle: " << titleStep->getSubtitle() << endl;
                                        }
                                        else if (TextStep *textStep = dynamic_cast<TextStep *>(steps[idx]))
                                        {
                                            file << "Text Step - Title: " << textStep->getTitle() << ", Copy: " << textStep->getCopy() << endl;
                                        }
                                        if (TitleStep *titleStep = dynamic_cast<TitleStep *>(steps[idx]))
                                        {
                                            file << "Title Step - Title: " << titleStep->getTitle() << ", Subtitle: " << titleStep->getSubtitle() << endl;
                                        }
                                        else if (TextStep *textStep = dynamic_cast<TextStep *>(steps[idx]))
                                        {
                                            file << "Text Step - Title: " << textStep->getTitle() << ", Copy: " << textStep->getCopy() << endl;
                                        }
                                        else if (TextInput *textInputStep = dynamic_cast<TextInput *>(steps[idx]))
                                        {
                                            file << "Text Input Step - Description: " << textInputStep->getDescription() << ", Text Input: " << textInputStep->getTextInput() << endl;
                                        }
                                        else if (NumberInput *numberInputStep = dynamic_cast<NumberInput *>(steps[idx]))
                                        {
                                            file << "Number Input Step - Description: " << numberInputStep->getDescription() << ", Number Input: " << numberInputStep->getNumberInput() << endl;
                                        }
                                        else if (CalculusStep *calculusStep = dynamic_cast<CalculusStep *>(steps[idx]))
                                        {
                                            file << "Calculus Step - Steps: " << calculusStep->getSteps() << ", Operation: " << calculusStep->getOperation() << endl;
                                        }
                                        else if (DisplayStep *displayStep = dynamic_cast<DisplayStep *>(steps[idx]))
                                        {
                                            file << "Display Step - Step: " << displayStep->getStep() << endl;
                                        }
                                        else if (TextFileInputStep *textFileInputStep = dynamic_cast<TextFileInputStep *>(steps[idx]))
                                        {
                                            file << "Text File Input Step - Description: " << textFileInputStep->getDescription() << ", File Name: " << textFileInputStep->getFile_name() << endl;
                                        }
                                        else if (CSVFileInputStep *csvFileInputStep = dynamic_cast<CSVFileInputStep *>(steps[idx]))
                                        {
                                            file << "CSV File Input Step - Description: " << csvFileInputStep->getDescription() << ", File Name: " << csvFileInputStep->getFile_name() << endl;
                                        }
                                        else if (OutputStep *outputStep = dynamic_cast<OutputStep *>(steps[idx]))
                                        {
                                            file << "Output Step - Step: " << outputStep->getStep() << ", File Name: " << outputStep->getFile_name()
                                                 << ", Title: " << outputStep->getTitle() << ", Description: " << outputStep->getDescription() << endl;
                                        }
                                    }

                                    myFlow.addStep(new OutputStep(index, nameFile, titleOutput,descriptionOutput));

                                    cout << "Do you want to add another step? (y/n): ";
                                    string answer;
                                    getline(cin, answer);
                                    if (answer != "y")
                                    {
                                        break;
                                    }
                                }

                                file.close();
                                break;
                            }
                            case 10:
                            {
                                myFlow.addStep(new EndStep("END"));
                                cout << "Ending input of steps." << endl;
                                done = true;
                                break;
                            }
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                                break;
                            }
                        }

                        catch (const InvalidIntegerInputException &ex)
                        {
                            cout << "Error: " << ex.what() << endl;
                            // Tratează eroarea sau gestionează situația
                        }
                        catch (const InvalidFloatInputException &ex)
                        {
                            cout << "Error: " << ex.what() << endl;
                            // Tratează eroarea sau gestionează situația
                        }
                    }

                    auto now = chrono::system_clock::now();
                    auto now_c = chrono::system_clock::to_time_t(now);

                    // covertim timpul intr-un string
                    string timestamp = ctime(&now_c);

                    cout << "Flow created at: " << timestamp << endl;

                    cout << "Flow Steps:\n";
                    myFlow.displayStepsInfo();

                    cout << "Number of error messages received: " << errorCount + errorCountInt << endl; // Afișarea numărului de erori

                    writeFlowToFile(myFlow, "flow.txt");
                }
                break;
            }

            case 2:
            {
                vector<Flow> flows = readFlowsFromFile("flow.txt");

                cout << "Flows available for execution: " << endl;
                for (const auto &flow : flows)
                {
                    cout << flow.getFlowTitle() << endl;
                }

                cin.ignore();
                string chosenFlowTitle;
                cout << "Enter the name of the flow you want to run: ";
                getline(cin, chosenFlowTitle);

                bool found = false;
                Flow chosenFlow("temp");

                for (const auto &flow : flows)
                {
                    if (flow.getFlowTitle() == chosenFlowTitle)
                    {
                        chosenFlow = flow;
                        found = true;
                        break;
                    }
                }

                if (found == true)
                {
                    int skippedScreensCount = runFlow(chosenFlow);
                    cout << "The screen was skipped " << skippedScreensCount << " times." << endl;

                    // Incrementăm numărul de rulări pentru flow-ul specificat sau îl adăugăm în map
                    flowRuns[chosenFlow.getFlowTitle()]++;
                }
                else
                {
                    cout << "Flow not found!" << endl;
                }

                break;
            }
            case 3:
            {
                cin.ignore();
                string flowTitleToDelete;
                cout << "Enter the name of the flow you want to delete: ";
                getline(cin, flowTitleToDelete);
                cout << endl;

                deleteFlowFromFile("flow.txt", flowTitleToDelete);
                break;
            }

            default:
                cout << "Invalid choice. Please try again!" << endl;
                break;
            }
        } while (choice < 1 || choice > 3);

        if (askForContinue())
        {
            cout << "Enter your choice: " << endl;

            cout << "1. Create a flow. " << endl;
            cout << "2. Run a flow. " << endl;
            cout << "3. Delete a flow. " << endl;
        }
        else
        {
            cout << "Exiting program..." << endl;
            break;
        }
    } while (true);

    cout << "Flow titles and their run counts:" << endl;
    for (const auto &pair : flowRuns)
    {
        cout << "Flow Title: " << pair.first << ", Runs: " << pair.second << endl;
    }

    return 0;
}