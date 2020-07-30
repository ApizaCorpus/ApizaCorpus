# Apiza WoZ Studies on API Usage with a Simulated Virtual Assistant
## allegro/

This folder contains the raw data for each study using the allegro scenario. It is organized as follows:

* sessions/
    * Contains folders for each study session using the allegro scenario. The names of the folders describe the session ID and on which date that session took place; for instance, the folder 16_20181016 was the 16th session of the Apiza studies (with ID# 16), taking place on October 16, 2018. Each folder contains some combination of the following files 
        * allegro_tasks.c
            * The code file edited by the programmer.
        * chatlog.txt
            * The chatlog between the programmer and the wizard.
        * comments.txt
            * Comments about the study session made by the programmer. If the comments were solicited by the study coordinator, those messages are included as well.
        * entry.txt
            * The scores provided by the programmer on the entry survey. These scores are aligned with the questions in entry_survey.txt.
        * exit.txt
            * The scores provided by the programmer on the exit survey. These scores are aligned with the questions in exit_survey.txt.
        * files/
            * Messages that are too long to send in Slack are instead attached and sent as text files; this folder contains those text files. 
        * history.txt
            * Contains the programmer's internet browsing history during the course of the study.
        * metadata.txt
            * Reports the ID of the wizard and programmer in this session.
        * score.txt 
            * Reports the programmer's completion of each task in the session. A score of 0 indicates that the task was not attempted; a score of 1 indicates that the task was attempted but not successfully completed; a score of 2 indicates that the task was successfully completed.

* entry_survey_questions.txt
    * The list of questions asked of participants in the entry survey in the allegro scenario.

* exit_survey_questions.txt
    * The list of questions asked of participants in the exit survey.

* skeleton_code.c
    * The skeleton code provided to programmers at the start of the allegro scenario.

* task_description.pdf
    * The document given to programmers describing the study parameters and tasks in the allegro scenario.