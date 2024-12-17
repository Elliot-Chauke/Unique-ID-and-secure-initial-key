#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QRegExp>
#include <QRegularExpression>
#include <cstdlib>
#include <ctime>

//function to generate unique ID
QString generateUniqueID(const QString& fullName)
{
    //Split the full name into parts by spaces
    QStringList names= fullName.split(" ",QString::SkipEmptyParts);
    QString firstName=names[0];
    QString lastName;
    QString middleName;

    //Make last part be last name and if the is third one make it middle name
    if(names.size()>1)
    {
        lastName=names.back();
    }
    if(names.size()>2)
    {
        middleName=names[1];
    }

//Make the first letter upper case and add it to uniqueID
 QString uniqueID;
 uniqueID.append(firstName[0].toUpper());

 //If middle name exist add the upper case first letter to unique id or use last name first upper case letter
if(!middleName.isEmpty())
{
    uniqueID.append(middleName[0].toUpper());
}
else
{
    uniqueID.append(lastName[0].toUpper());
}

//Remove whitespaces and count the letters
   QRegExp whitespace("\\s");
   QString letters = fullName;
   letters.remove(whitespace);
   int letterCount=letters.length();

//Convert the count to 4 digit string and add to the unique id
QString numeric = QString::number(letterCount).rightJustified(4, '0');

uniqueID.append(numeric);



return uniqueID;
}



//Function to generate initial Key
QString generateInitialKey(const QString& fullName)
{
    QString initialKey;
    QString vowels = "aeiou";
    QString consonants = "bcdfghjklmnpqrstvwxyz";


    srand(time(0));//Random number generate with current time

    //Flag if a vowel or consonant has been found
    bool VowelFound = false;
    bool ConsonantFound = false;

    //Loop to ensure vowel and consonant are included in the initial key
    while (!VowelFound || !ConsonantFound)
    {
        int randomNum = qrand() % fullName.size();//generate random characters in the full name
        QChar randomChar = fullName.at(randomNum).toLower();//make the letter lower case

        //Check for vowel and consonant and also ignore spaces
        if (randomChar != ' ') {
            if (vowels.contains(randomChar) && !VowelFound)
            {
                initialKey += randomChar;
                VowelFound = true;
            } else if (consonants.contains(randomChar) && !ConsonantFound) {
                initialKey += randomChar;
                ConsonantFound = true;
            }


        }
    }

     //Add the random characters to initial key
    for (int i = 0; i < 4; i++)
    {
        int randomIndex = qrand() % fullName.size();
        QChar randomChar = fullName.at(randomIndex).toLower();

        if (randomChar != ' ' && !initialKey.contains(randomChar)) {
            initialKey += randomChar;
        } else {
            i--;
        }
    }

    return initialKey;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

       //Ask the user to enter full name
       QString fullName = QInputDialog::getText(0, "Enter Your Full Name", "Full Name:");

       QRegularExpression regex("^[a-zA-Z\\s]+$");//Validate full name


        //Display error if full name is not valid
        if (!fullName.contains(regex) || fullName.count(' ') == 0)
        {
            QMessageBox::warning(0, "Invalid name", "Please enter a valid full name(letters and spaces).");
            QString fullName = QInputDialog::getText(0, "Enter Your Full Name", "Full Name:");
            return 0;
        }


    //Display full name, unique ID and initial key
    QString uniqueID = generateUniqueID(fullName);
    QString initialKey = generateInitialKey(fullName);
    QMessageBox::information(0,"User Credentials",QString("Full Name : %1\nUnique ID is : %2\nInitial Key is : %3").arg(fullName).arg(uniqueID).arg(initialKey));


    return 0;
}
