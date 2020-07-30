# Apiza WoZ Studies on API Usage with a Simulated Virtual Assistant
## experiment_results/

This folder contains the formatted results of both studies (task completion and user satisfaction). It is organized as follows:

* experimental_results.pkl
    * The dialogue act annotations for each study session in the Python pickle file format (created using Pickle protocol 3). The pickle object is organized as follows:
    
    ```
    {
        Session_ID (an int in [1,30]):
            {
                "metadata": {
                    "wizard": Wizard_ID (e.g. "06"), 
                    "programmer": Programmer_ID (e.g. "28")
                },

                "library": Either "allegro" or "libssh",

                "score": A dict associating each task id (an int, e.g. 3) with a score (0, 1, or 2),

                "entry": A dict associating each entry survey question id (an int, e.g. 1, correlating to a specific line in the entry_survey_questions.txt file) with the programmer's answer (a string),

                "exit": A dict associating each exit survey question id (an int, e.g. 1, correlating to a specific line in the entry_survey_questions.txt file) with the programmer's answer (a string),

                "chatlog": A dict containing the unformatted Slack chatlog.
            }
        }
    }
    ```
    
* experimental_results.csv
    * The experimental results in the .csv file format. The first row is a header defining the data fields, and each subsequent row corresponds to an experimental session. The data fields are as follows:
        * pro_id - The ID of the programmer in the session.
        * wiz_id - The ID of the wizard in the session.
        * lib - The library used in the session.
        * num_pro_mess - The number of messages sent by the programmer in the session.
        * avg_pro_len - The average length (in characters) of the programmer's messages in the session.
        * num_wiz_mess - The number of messages sent by the wizard in the session.
        * avg_wiz_len - The average length (in characters) of the wizard's messages in the session.
        * num_tot_mess - The total number of messages (wizard+programmer) in the session.
        * avg_tot_len - The average length of all messages (wizard+programmer) in the session.
        * total_score - The programmer's "score" on the programming tasks.
        * total_exit - The total of all responses in the exit survey filled out by the programmer.
        * e1_expected_behavior - The programmer's response to Question 1 on the exit survey.
        * e2_comprehension - The programmer's response to Question 2 on the exit survey.
        * e3_coparable_interface - The programmer's response to Question 3 on the exit survey.
        * e4_future_use - The programmer's response to Question 4 on the exit survey.
        * e5_task_ease - The programmer's response to Question 5 on the exit survey.
        * e6_comprehensibility - The programmer's response to Question 6 on the exit survey.
        * e7_system_response - The programmer's response to Question 7 on the exit survey.
        * e8_user_expertise - The programmer's response to Question 8 on the exit survey.
        * e9_interaction_pace - The programmer's response to Question 9 on the exit survey. 


