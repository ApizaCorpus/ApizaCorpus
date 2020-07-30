# Apiza WoZ Studies on API Usage with a Simulated Virtual Assistant
## annotations/

This folder contains the dialogue act annotations for each study session. It is organized as follows:

* annotations.pkl 
    * Contains the dialogue act annotations for each study session in the Python pickle file format (created using Pickle protocol 3). The pickle object is organized as follows:
    
    ```
    {
        Session_ID (an int in [1,30]):
        {
            "lib": A string denoting the library used for the study (either "allegro" or "libssh"),

            "utterances":
            {
                Dialogue_Act_ID (number):
                {
                    "message_id": A number indicating to which message the dialogue act belongs,

                    "text": A string containing the text of the dialogue act,

                    "speaker": A string indicating whether this dialogue act was in a message sent by the Programmer or Apiza (the Wizard),

                    "link": If this dialogue act has a backwards-facing dialogue act type, this is a number indicating the id of the prior dialogue act with which this act has a relationship,

                    "backward-facing": If this dialogue act has a backwards-facing dialogue act type, this is a string indicating that type,

                    "illocutionary": A string indicating the high-level, illocutionary AMI dialogue act label assigned to this dialogue act,

                    "api": A list of strings indicating the API dialogue act types assigned to this dialogue act,

                    "traceability": A list of any specific API components that are the "topic" of the dialogue act type.
                }
            }
        }
    }
    ```
    
* csv/
    * Contains the dialogue act annotations for each study session in the .csv file format. Each file is identified with a unique study session ID between 01 and 30. The first row in each **apiza_labels_##.csv** file is a header defining the data fields, and each subsequent row corresponds to a single dialogue act.  The data fields are as follows:
        * line - The "line number," indicating to which message the dialogue act belongs
        * id - A unique ID
        * speaker - Indicates whether this dialogue act was in a message sent by the Programmer or Apiza (the Wizard).
        * text - The text of the dialogue act. 
        * ami_label - The high-level, illocutionary AMI dialogue act label assigned to this dialogue act.
        * link - If this dialogue act has a backwards-facing dialogue act type, this field indicates the id of the prior dialogue act with which this act has a relationship.
        * relationship - If this dialogue act has a backwards-facing dialogue act type, this field indicates that type.
        * api_labels - Lists the API dialogue act types assigned to this dialogue act.
        * topic - Lists any specific API components that are the "topic" of the dialogue act type (the "traceability" annotations).
        * entities - Not currently used.


