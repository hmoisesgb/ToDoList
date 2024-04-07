#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>

class Task {
    public:
        //The constructor sets the description to the one provided by the user, and sets
        //the initial value of the completed variable to false
        Task(std::string desc){
            description = desc;
            completed = false;
        }
        
        //This method changes the completed variable to true
        void completeTask(){
            completed = true;
        }
        
        //This method shows the description and the current status of the task
        //checking if it is complete or not
        void displayInformation() {

            if (completed == true)
            {
                std::cout << " Description: " << description << " | " << "Completed: Yes";
            }
            else 
            {
                std::cout << " Description: " << description << " | " << "Completed: No";
            }
            
        }

        //This method returns a string representation to save in the text file
        //the string consists of the description of the task and the completion
        //status separated by the delimiter '|'
        std::string getStringRepresentation() {

            std::string representation;

            if (completed == true)
            {
                representation = description+ "|Completed\n";
            }
            else
            {
                representation = description + "|Pending\n";
            }

            return representation;
        }
    private:
        //This are the variables of the class, these variables save the description
        //and the completion status of the object.
        std::string description;
        bool completed;
};

class TasksManager {
    public:

        //This method starts the program and shows the user a menu with the program options
        //this method also uses several methods created to manage the list of tasks.
        void Start() {
            
            //This variable will get edited by user input and will help to select an option
            //in the menu.
            int menuOption = 0;

            //This is a while loop that will only end when the user selects
            //the option to exit the program.
            while (1)
            {
                std::cout << "Please select an option from the menu: " << "\n";
                std::cout << "1. Add to do task" << "\n";
                std::cout << "2. Remove task" << "\n";
                std::cout << "3. Complete task" << "\n";
                std::cout << "4. View tasks" << "\n";
                std::cout << "5. Save tasks to a file" << "\n";
                std::cout << "6. Load tasks from a file" << "\n";
                std::cout << "7. Exit the program" << "\n";

                //These lines of code get input from the user using the
                //getline() method and then parses it to int using the stoi method
                std::string input;
                std::getline(std::cin, input);
                menuOption = std::stoi(input);

                //After the user inputs the number of the option, the program will check
                //the option selected by the user and will run the selected methods
                if (menuOption == 1)
                {
                    AddTask();

                }
                else if (menuOption == 2)
                {
                    RemoveTask();
                }
                else if (menuOption == 3)
                {
                    CompleteTask();
                }
                else if (menuOption == 4)
                {
                    ViewTasks();
                }
                else if (menuOption == 5)
                {
                    SaveTasks();
                }
                else if (menuOption == 6)
                {
                    LoadTasks();
                }
                else if (menuOption == 7)
                {
                    //Once the user selects the option to exit, the program will break
                    //out of the loop
                    std::cout << "Thank you for using the program. Have a nice day!";
                    break;
                }
                else {
                    //If the user does not select a valid option this message will show
                    std::cout << "Please select a valid option";
                }
            }
        }

    private:
        //This task manager will save each created task in a list named Tasks
        std::list<Task> Tasks;

        //The add task method asks the user for the description of their task,
        //and creates a new task using the information provided by the user,
        //then it adds the new object to the Tasks list.
        void AddTask() {
            std::string taskDescription;
            std::cout << "Please input the description of your task: ";
            std::getline(std::cin, taskDescription);
            Task task(taskDescription);
            Tasks.push_back(task);
            std::cout << "Task added successfully" << "\n";
        }

        //This method shows the user each created task, and then asks for the
        //number of the task they want to delete to delete it.
        void RemoveTask() {

            //First I created a taskToDelete integer to save the number of the task to delete.
            int taskToDelete = 0;

            //Then the program shows the tasks using the ViewTasks method and asks the user
            //the number of the task to remove.
            ViewTasks();
            std::cout << "Please select the number of the task you want to delete: ";

            //These lines of code get input from the user using the
            //getline() method and then parses it to int using the stoi method
            std::string input;
            std::getline(std::cin, input);
            taskToDelete = std::stoi(input);

            //After getting the number from the user, the program substacts 1
            //from the taskToDelete, so the correct index is deleted.
            taskToDelete--;

            //I then create an iterator and advance it according to the number selected
            //by the user, and then the selected task gets removed using the erase method.
            std::list<Task> ::iterator it;
            it = Tasks.begin();
            advance(it, taskToDelete);
            Tasks.erase(it);

            std::cout << "Task removed successfully" << "\n";
        }

        //This method shows the user the list of tasks and asks the user which task they completed,
        //then it uses the completeTask() method of the object selected to change the completed
        //value to true.
        void CompleteTask() {

            //First I created a taskToComplete integer to save the number of the task to complete.
            int taskToComplete;
            ViewTasks();
            std::cout << "Please select the number of the task you want to complete: ";

            //These lines of code get input from the user using the
            //getline() method and then parses it to int using the stoi method
            std::string input;
            std::getline(std::cin, input); 
            taskToComplete = std::stoi(input);
            
            //After getting the number from the user, the program substacts 1
            //from the taskToComplete, so the correct index is completed.
            taskToComplete--;

            //I then create an iterator and advance it according to the number selected
            //by the user, and then the selected task gets completed by using the completeTask() method.
            std::list<Task> ::iterator it;
            it = Tasks.begin();
            advance(it, taskToComplete);
            it->completeTask();

            std::cout << "Task completed succesfully" << "\n";
        }

        //The view tasks method uses a range-based for loop that iterates through
        //each object in the list, and displays the information in the console
        //using the displayInformation() method of each object
        void ViewTasks() {

            //The i variable is just here to show the user a number for each task
            //and it increases by 1 for every task in the list.
            int i = 1;
            for (Task task : Tasks) {
                std::cout << i, task.displayInformation();
                std::cout << "\n";
                i++;
            }
            std::cout << "\n";
        }

        //The SaveTasks method asks the user for a filename and then saves the
        //tasks to a text file.
        void SaveTasks() {

            std::fstream file;
            std::string filename;

            //First the program asks the user the filename where they want to save the tasks
            std::cout << "Please enter the filename of your tasks file: ";

            //After this, the program gets the filename using getline() and saving the data in the filename string
            std::getline(std::cin, filename);

            //Then using the filename, the program opens the file using an fstream in write mode.
            file.open(filename, std::ios::out);

            //While the file is open, the program will use a for loop for each task in the Tasks list
            //and each task using the getStringRepresentation method.
            if (file.is_open())
            {
                for (auto it : Tasks)
                {
                    file << it.getStringRepresentation();
                }
                std::cout << "File saved successfully in " + filename << "\n";
                file.close();
            }
        }

        //This LoadTasks method, gets the data from a text file and adds each task in the file
        //to the Tasks list.
        void LoadTasks() {

            std::string filename;
            std::fstream file;

            //First the program asks the user the filename where they want to load the tasks
            std::cout << "Please enter the filename of your tasks file: ";

            //After this, the program gets the filename using getline() and saving the data in the filename string
            std::getline(std::cin, filename);

            //Then using the filename, the program opens the file using an fstream in read mode.
            file.open(filename, std::ios::in);

            //While the file is open, the program will use a while loop that checks every line in the
            //text file to create a new Task object to add to the list of tasks.
            if (file.is_open()) {

                //First I created a variable named line to save each line of text
                std::string line;

                //Then using a while loop, the program reads each line of the text file
                while (std::getline(file, line)) {

                    //Then I declare the items that will help me to split the strings
                    //into the description and the completed status of the task.
                    std::stringstream ss(line);
                    std::string part;
                    std::vector<std::string> parts;
                    char delimiter = '|';

                    //As each line in the text file consist in the description of the task
                    //and the completed status separated by the delimiter '|' I use a while
                    //loop to split the string and add it to the parts vector
                    while (std::getline(ss,part,delimiter))
                    {
                        parts.push_back(part);
                    }

                    //After the while loop the parts vector will consist on 2 strings,
                    //the first one is the description of the task, and I use the first
                    //part of the vector to create a Task object using the description in the text line.
                    Task task(parts[0]);

                    //After this, this if will check if the task is completed or not, and if it is
                    //completed it will use the completeTask() method
                    if (parts[1] == "Completed")
                    {
                        task.completeTask();
                    }

                    //Finally the task object is added to the Tasks list
                    Tasks.push_back(task);
                }

                std::cout << "File loaded successfully" << "\n";
                file.close();
            }
        }
};

int main()
{
    //The main function just creates a task manager object and uses the Start function to show the menu
    TasksManager tasks;
    tasks.Start();
    return 0;
}
