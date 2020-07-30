# Apiza WoZ Studies on API Usage with a Simulated Virtual Assistant
## libssh/

This folder contains the raw data for each study using the libssh scenario. It is organized as follows:

* sessions/
    * Contains folders for each study session using the libssh scenario. The names of the folders describe the session ID and on which date that session took place; for instance, the folder 03_20180614 was the 3rd session of the Apiza studies (with ID# 03), taking place on June 14, 2018. Each folder contains some combination of the following files:
        * ssh_tasks.c
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

* entry_survey.txt
    * The list of questions asked of participants in the entry survey in the libssh scenario.

* exit_survey.txt
    * The list of questions asked of participants in the exit survey.

* task_description.pdf
    * The document given to programmers describing the study parameters and tasks in the libssh scenario.