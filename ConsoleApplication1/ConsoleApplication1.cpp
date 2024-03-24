#include <iostream>
#include <string>
#include <list>


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
                std::cout << "5. Exit the program" << "\n";

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
};

int main()
{
    //The main function just creates a task manager object and uses the Start function to show the menu
    TasksManager tasks;
    tasks.Start();
    return 0;
}
