#include <SFML/Graphics.hpp>
#include<iostream>
#include<algorithm>
#include<cctype>
#include<string>
using namespace std;
using namespace sf;

#define usersSize 100


RenderWindow window(VideoMode(1506, 957), "Bank System", Style::Default | Style::Close);
Font ROCKEB, COURIER;
int section = 1;
int p2section = 1;
bool IsSigninTrue1 = false;
bool IsSigninTrue2 = false;

//---------------------------------CMD structs-------------------------------
struct account
{
    string inputusername;
    string inputpass;
    string inputemail;
    string inputage;
    string inputnum;
    string inputbalance;
    string emailSignin;
    string passSignin;
};

struct user
{
    account userAccount;
    int accNum;
};

//------------------------------------- CMD Functions --------------------------------


//----------------------------------------- Header ------------------------------------
struct Header
{
    Text user, bank;
}header;
//------------------------------------------ HITBOX ------------------------------------
struct hitbox
{
    RectangleShape box;
    void setup(float width, float height, float posX, float posY)
    {
        box.setSize(Vector2f(width, height));
        box.setPosition(posX, posY);
        box.setFillColor(Color(20, 255, 236));
    }
}usernamebox, emailbox, passbox, phoneno, Age, signinbox, balancebox, signupbox, emailsigninbox, passsigninbox, ButtonSigninBox,backbox;
//----------------------------------------- BODY SETUP ----------------------------------------------------------
struct bodyText
{
    Text text;
}signup2, balance, signin, signintext, username, email, password, phonenum, age, inputTextusername, inputtextemail, inputtextpass, inputtextnum, inputtextage, inputtextbalance, emailTextsignin, passwordTextsignin;
//----------------------------------------- TEXT SETUP ------------------------------------------------------------
void textSetup(bodyText& textname, string written, Font fontname, float size, Color color, float posx, float posy)
{
    COURIER.loadFromFile("COURIER.ttf");
    textname.text.setString(written);
    textname.text.setFont(COURIER);
    textname.text.setCharacterSize(size);
    textname.text.setFillColor(color);
    textname.text.setPosition(posx, posy);
}
//------------------------------------------- OBJECT ----------------------------
struct object
{
    Sprite sprite;
    Texture texture;
    void setupObject(string location, int posX, int posY)
    {
        texture.loadFromFile(location);
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
    }
};
//-------------------------------------------- func --------------------------------------
void drawBodyText(user& temp, bodyText signup2, bodyText signin, bodyText signintext, bodyText username, bodyText email, bodyText password, bodyText phonenum, bodyText age, object& errorline0, object& errorline, object& errorline2, object& errorline3, object& errorline4, object& errorline5, bodyText& balance, int intnum, int intage, int intbalance);
void setBodytext(bodyText& signup2, bodyText& signin, bodyText& signintext, bodyText& username, bodyText& email, bodyText& password, bodyText& phonenum, bodyText& age, bodyText& balance);

void Draw(user& temp, object& Button, object& Background, object& Button2, object& typeline, object& typeline2, object& typeline3, object& typeline4, object& typeline5, object& typeline6, object& typeline7, object& typeline8, object& SignInBackground, object& lockIcon, object& loginIcon, object& errorline0, object& errorline, object& errorline2, object& errorline3, object& errorline4, object& errorline5, object& errorline6, object& errorline7, int intnum, int intage, int intbalance,object& back);

void drawHeader(Header header);
void setHeader(Header& header);

void mousepo(Vector2i&);
//----------------------------------------------- GLOBAL VARIABLES -------------------------------
bool isEnterPressed = false;
bool AlreadyPressed = false;
bool IsSignUpPressed = false;
bool LeftMouseClicked = false;
bool signinBoxPressed = false;

string domain = "@user.bank";
//-------------------------------------------Remove spaces -----------------------------------
string removeSpaces(string input) {
    string output;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != ' ')
            output += input[i];
    }
    return output;
}
//--------------------------------------------Backspace---------------------------------------
void backspaceDelete(Event& event, string& text)
{
    if (event.type == Event::TextEntered)
    {
        if (event.text.unicode != 8)
        {
            if (section <= 3)
            {
                text += event.text.unicode;
                text = removeSpaces(text);
            }
            else
            {
                if (isdigit(event.text.unicode))
                    text += event.text.unicode;
                text = removeSpaces(text);
            }
        }
        else
        {
            if (!text.empty())
                text.pop_back();

        }
    }
    //---------------------------- Detect whitespaces(space, tab,newline) -------------------------
    if (event.text.unicode == 13)
    {
        text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());

    }
}
//-----------------------------------------------------------------------------------MAIN----------------------------------------------------------------------------------------------------------
int main()
{
    bool safe = true;
    int UserIndex = 0;
    object Button, Background, errorline0, errorline, errorline2, Button0, typeline, typeline2, typeline3, typeline4, typeline5, typeline6, typeline7, typeline8, SignInBackground, lockIcon, loginIcon, errorline3, errorline4, errorline5, errorline6, errorline7,back;
    user temp, users[usersSize];
    long long intnum = 0, intage = 0, intbalance = 0;
    //------------------------------------------SIGN UP PAGE-------------------------------------------------
    Background.setupObject("background (2).png", 0, 0);
    Button0.setupObject("button.png", 460, 630);
    typeline.setupObject("Type Line.png", 450, 310);//username
    errorline0.setupObject("Error Line.png", 450, 288);
    typeline2.setupObject("Type Line.png", 450, 370);//Email
    errorline.setupObject("Error Line.png", 450, 348);
    typeline3.setupObject("Type Line.png", 450, 430);//pass
    errorline2.setupObject("Error Line.png", 450, 408);
    typeline4.setupObject("Type Line.png", 450, 490);//number
    errorline3.setupObject("Error Line.png", 450, 468);
    typeline5.setupObject("Type Line.png", 450, 550);//age
    errorline4.setupObject("Error Line.png", 450, 528);
    typeline6.setupObject("Type Line.png", 450, 610);//balance
    errorline5.setupObject("Error Line.png", 450, 588);
    //------------------------------------------Hit Boxes in sign up page-------------------------------------
    usernamebox.setup(470, 30, 440, 280);
    emailbox.setup(470, 30, 440, 340);
    passbox.setup(470, 30, 440, 400);
    phoneno.setup(470, 30, 440, 460);
    Age.setup(470, 30, 440, 520);
    balancebox.setup(470, 30, 440, 580);
    signinbox.setup(450, 30, 870, 750);
    signupbox.setup(255, 70, 580, 730);
    //------------------------------------------SIGN IN PAGE-------------------------------------------------
    SignInBackground.setupObject("SignInBackground.png", 0, 0);
    Button.setupObject("button.png", 460, 500);
    lockIcon.setupObject("lockicon.png", 980, 490);
    loginIcon.setupObject("loginicon.png", 980, 285);
    typeline7.setupObject("Type Line.png", 520, 310);
    typeline8.setupObject("Type Line.png", 520, 510);
    errorline6.setupObject("Error Line.png", 520, 288);
    errorline7.setupObject("Error Line.png", 520, 488);
    back.setupObject("back.png", 100, 700);
    //------------------------------------------Hit Boxes in sign in page-------------------------------------
    emailsigninbox.setup(470, 30, 520, 280);
    passsigninbox.setup(470, 30, 520, 485);
    backbox.setup(101, 101, 100, 700);




    setHeader(header);
    setBodytext(signup2, signin, signintext, username, email, password, phonenum, age, balance);


    //*********************************************************************** MAIN LOOP "GAME LOOP" **********************************************************************************************************
    while (window.isOpen())
    {
        Vector2i mouseposition = Mouse::getPosition(window);
        mousepo(mouseposition);


        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonReleased:
                switch (event.key.code)
                {
                case Mouse::Left:

                    break;
                }
                break;
            }
            //------------------------------ End of main switch ------------------------------------

            if (event.type == Event::KeyReleased && isEnterPressed)
            {
                section++;
                p2section++;
                if (p2section > 2 || section > 6)
                {
                    p2section = 1;
                }
                isEnterPressed = false;
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                isEnterPressed = true;

            }
            //-----------------------------------SAFE------------------------------------------

            if (Mouse::isButtonPressed(Mouse::Left) && safe)
            {
                LeftMouseClicked = true;
                UserIndex++;
            }



            if (event.type == Event::TextEntered)
            {


                switch (section)
                {
                    //---------------------------------------- username --------------------------------------
                case 1:
                {
                    backspaceDelete(event, temp.userAccount.inputusername);
                    textSetup(inputTextusername, temp.userAccount.inputusername, COURIER, 25, Color(255, 228, 201), 450, 280);
                    break;
                }
                //------------------------------------------- email --------------------------------------
                case 2:
                {
                    backspaceDelete(event, temp.userAccount.inputemail);
                    textSetup(inputtextemail, temp.userAccount.inputemail, COURIER, 25, Color(255, 228, 201), 450, 340);
                    break;
                }

                //------------------------------------------ password -------------------------------------
                case 3:
                {
                    backspaceDelete(event, temp.userAccount.inputpass);
                    textSetup(inputtextpass, temp.userAccount.inputpass, COURIER, 25, Color(255, 228, 201), 450, 400);
                    break;
                }
                //------------------------------------------ number --------------------------------------
                case 4:
                {
                    backspaceDelete(event, temp.userAccount.inputnum);
                    textSetup(inputtextnum, temp.userAccount.inputnum, COURIER, 25, Color(255, 228, 201), 450, 460);
                    break;
                }
                //------------------------------------------ Age -----------------------------------------
                case 5:
                {
                    backspaceDelete(event, temp.userAccount.inputage);
                    textSetup(inputtextage, temp.userAccount.inputage, COURIER, 25, Color(255, 228, 201), 450, 520);
                    break;
                }
                //------------------------------------------ balance -----------------------------------------
                case 6:
                {
                    backspaceDelete(event, temp.userAccount.inputbalance);
                    textSetup(inputtextbalance, temp.userAccount.inputbalance, COURIER, 25, Color(255, 228, 201), 450, 580);
                    break;
                }


                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                if (IsSignUpPressed || AlreadyPressed)
                {
                    section = 0;
                    switch (p2section)
                    {

                    case 1:
                    {
                        backspaceDelete(event, temp.userAccount.emailSignin);
                        textSetup(emailTextsignin, temp.userAccount.emailSignin, COURIER, 25, Color(255, 228, 201), 520, 275);
                        //searching for the signin email if it equals the signup email

                        if (temp.userAccount.emailSignin == users[UserIndex].userAccount.inputemail)
                        {
                            IsSigninTrue1 = true;
                        }
                        else
                            IsSigninTrue1 = false;


                        break;
                    }

                    case 2:
                    {
                        backspaceDelete(event, temp.userAccount.passSignin);
                        textSetup(passwordTextsignin, temp.userAccount.passSignin, COURIER, 25, Color(255, 228, 201), 520, 475);
                        if (temp.userAccount.passSignin == users[UserIndex].userAccount.inputpass)
                        {
                            IsSigninTrue2 = true;
                        }
                        else
                            IsSigninTrue2 = false;

                        break;
                    }
                    }
                }

            }
        }
        //------------------------------------------------------- SAVING -------------------------------------------------------
        if (IsSignUpPressed)
        {

            users[UserIndex].userAccount.inputusername = temp.userAccount.inputusername;
            users[UserIndex].userAccount.inputemail = temp.userAccount.inputemail;
            users[UserIndex].userAccount.inputpass = temp.userAccount.inputpass;
            users[UserIndex].userAccount.inputage = temp.userAccount.inputage;
            users[UserIndex].userAccount.inputbalance = temp.userAccount.inputbalance;


            cout << users[UserIndex].userAccount.inputusername << endl;
            cout << users[UserIndex].userAccount.inputemail << endl;
            cout << users[UserIndex].userAccount.inputpass << endl;
            cout << users[UserIndex].userAccount.inputage << endl;
            cout << users[UserIndex].userAccount.inputbalance << endl;

        }

        //---------------------------------------------------------STOI-----------------------------------------------------------------------------------------------------------

        if (!temp.userAccount.inputage.empty())
        {
            intage = stoi(temp.userAccount.inputage);
        }
        if (!temp.userAccount.inputbalance.empty())
        {
            intbalance = stoi(temp.userAccount.inputbalance);
        }



        //---(-----"CHECK USERNAME" not empty -----)  (----------------------------------------------"CHECK EMAIL" must have @user.bank----------------------------------------------------------)    (-----------------------"CHECK PASSWORD" must be strong-----------------------)  (---------------------"CHECK NUMBER" 11 numbers-------------------------------)  (--"CHECK AGE" if user bigger than 18 then its safe to sginup)    (--------------------------"CHECK BALANCE" more than 200 pounds-----------)
        if (temp.userAccount.inputusername.empty() || temp.userAccount.inputemail.empty() || !(temp.userAccount.inputemail.rfind(domain) == temp.userAccount.inputemail.length() - domain.length()) || temp.userAccount.inputpass.empty() || temp.userAccount.inputpass.length() < 8 || temp.userAccount.inputnum.empty() || temp.userAccount.inputnum.length() != 11 || temp.userAccount.inputage.empty() || intage < 18 || temp.userAccount.inputbalance.empty() || intbalance < 200)
        {
            safe = false;
        }
        else
        {
            safe = true;
        }
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------





        window.clear();
        //------------------------------------------------------------------------------- DRAW -------------------------------------------------------------------------------------------------

        Draw(temp, Button, Background, Button0, typeline, typeline2, typeline3, typeline4, typeline5, typeline6, typeline7, typeline8, SignInBackground, lockIcon, loginIcon, errorline0, errorline, errorline2, errorline3, errorline4, errorline5, errorline6, errorline7, intnum, intage, intbalance,back);
        //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        window.display();
        if (safe)
            cout << "yup\n";
        else
            cout << "nuuuuh\n";
        cout << intage << endl;
        cout << intbalance << endl;
        cout << p2section << endl;
    }

    //***********************************************************************************END OF GAME LOOP*********************************************************************************************************
    return 0;
}
//-----------------------------------------------------------------------------------END OF MAIN----------------------------------------------------------------------------------------------------------


void Draw(user& temp, object& Button, object& Background, object& Button2, object& typeline, object& typeline2, object& typeline3, object& typeline4, object& typeline5, object& typeline6, object& typeline7, object& typeline8, object& SignInBackground, object& lockIcon, object& loginIcon, object& errorline0, object& errorline, object& errorline2, object& errorline3, object& errorline4, object& errorline5, object& errorline6, object& errorline7, int intnum, int intage, int intbalance,object& back)
{
    if (AlreadyPressed == false)
    {
        window.draw(Background.sprite);
        //------------------------window.draw(sprite);--------------------------------------
        window.draw(Button2.sprite);
        window.draw(typeline.sprite);
        window.draw(typeline2.sprite);
        window.draw(typeline3.sprite);
        window.draw(typeline4.sprite);
        window.draw(typeline5.sprite);
        window.draw(typeline6.sprite);
        //--------------------------------------func draw-------------------------------
        drawHeader(header);
        drawBodyText(temp, signup2, signin, signintext, username, email, password, phonenum, age, errorline0, errorline, errorline2, errorline3, errorline4, errorline5, balance, intnum, intage, intbalance);

    }

    if ((AlreadyPressed || IsSignUpPressed) && signinBoxPressed == false  )
    {
        window.draw(SignInBackground.sprite);
        window.draw(Button.sprite);
        window.draw(typeline8.sprite);
        email.text.setPosition(350, 270);
        window.draw(email.text);
        password.text.setPosition(270, 470);
        window.draw(password.text);
        window.draw(signin.text);
        window.draw(loginIcon.sprite);
        window.draw(lockIcon.sprite);
        window.draw(emailTextsignin.text);
        window.draw(passwordTextsignin.text);
        window.draw(typeline7.sprite);
        ButtonSigninBox.setup(255, 70, 580, 600);
        //signin email if it not  equals the signup email draw the error line
        if (p2section == 1)
        {
            if (!IsSigninTrue1)
            {
                window.draw(errorline6.sprite);
            }
        }
        if (p2section == 2)
        {
            if (!IsSigninTrue2)
            {
                window.draw(errorline7.sprite);
            }
        }
        window.draw(back.sprite);
    }
   
    if (signinBoxPressed )
    {
        window.draw(Background.sprite);
    }

}

//----------------------------HEADER--------------------------------------
void setHeader(Header& header)
{
    ROCKEB.loadFromFile("ROCKEB.ttf");
    header.user.setString("USER");
    header.user.setFont(ROCKEB);
    header.user.setFillColor(Color(255, 228, 201));
    header.user.setCharacterSize(30);
    header.user.setPosition(100, 10);
    header.bank.setString("BANK");
    header.bank.setFont(ROCKEB);
    header.bank.setFillColor(Color(255, 228, 201));
    header.bank.setCharacterSize(70);
    header.bank.setPosition(1000, 10);
}
void drawHeader(Header header)
{
    window.draw(header.user);
    window.draw(header.bank);
}
//------------------------------------------------------------------------------------------------------------------------------ BODY DRAW ------------------------------
void drawBodyText(user& temp, bodyText signup2, bodyText signin, bodyText signintext, bodyText username, bodyText email, bodyText password, bodyText phonenum, bodyText age, object& errorline0, object& errorline, object& errorline2, object& errorline3, object& errorline4, object& errorline5, bodyText& balance, int intnum, int intage, int intbalance)
{
    window.draw(signup2.text);
    window.draw(signintext.text);
    window.draw(username.text);
    window.draw(email.text);
    window.draw(password.text);
    window.draw(phonenum.text);
    window.draw(age.text);
    window.draw(balance.text);
    window.draw(inputTextusername.text);
    if (section == 1)
    {
        if (temp.userAccount.inputusername.empty())
        {
            window.draw(errorline0.sprite);
        }
    }
    window.draw(inputtextemail.text);

    //---------------- CHECK EMAIL IF IT HAS @user.bank ---------------------
    if (section == 2)
    {
        //                                          "stringname.rfind()" SEE THE LAST CHAR OR SUBTRACTING THE MAIN STRING WITH THE LAST STRING YOU WANT)
                                                                           //     ||
                                                                          //      \/ 
        if (temp.userAccount.inputemail.empty() || !(temp.userAccount.inputemail.rfind(domain) == temp.userAccount.inputemail.length() - domain.length()))
        {
            window.draw(errorline.sprite);
        }
    }
    //----------------------------------------------------------------------
    window.draw(inputtextpass.text);
    //-------------------------CHECK PASSWORD-------------------------------
    if (section == 3)
    {
        if (temp.userAccount.inputpass.empty() || temp.userAccount.inputpass.length() < 8)
        {
            window.draw(errorline2.sprite);
        }
    }
    //----------------------------------------------------------------------

    window.draw(inputtextnum.text);
    //-------------------------CHECK NUMBER---------------------------------
    if (section == 4)
    {
        if (temp.userAccount.inputnum.empty() || temp.userAccount.inputnum.length() != 11)
        {
            window.draw(errorline3.sprite);
        }
    }
    //----------------------------------------------------------------------

    window.draw(inputtextage.text);
    //-------------------------CHECK AGE------------------------------------
    if (section == 5)
    {
        if (temp.userAccount.inputage.empty() || intage < 18)
        {
            window.draw(errorline4.sprite);
        }
    }
    //----------------------------------------------------------------------

    window.draw(inputtextbalance.text);
    //-------------------------CHECK BALANCE-------------------------------
    if (section == 6)
    {
        if (temp.userAccount.inputbalance.empty() || intbalance < 200)
        {
            window.draw(errorline5.sprite);
        }
    }
    //----------------------------------------------------------------------
}
void setBodytext(bodyText& signup2, bodyText& signin, bodyText& signintext, bodyText& username, bodyText& email, bodyText& password, bodyText& phonenum, bodyText& age, bodyText& balance)
{
    textSetup(signup2, "SIGN UP", COURIER, 35, Color(33, 33, 33), 630, 740);
    textSetup(signintext, "Already have an account?", COURIER, 30, Color(255, 228, 201), 870, 750);
    textSetup(username, "Username:", COURIER, 45, Color(255, 228, 201), 210, 270);
    textSetup(email, "Email:", COURIER, 45, Color(255, 228, 201), 290, 330);
    textSetup(password, "Password:", COURIER, 45, Color(255, 228, 201), 210, 390);
    textSetup(phonenum, "Phone Number:", COURIER, 45, Color(255, 228, 201), 100, 450);
    textSetup(age, "Age:", COURIER, 45, Color(255, 228, 201), 350, 510);
    textSetup(balance, "Balance:", COURIER, 45, Color(255, 228, 201), 240, 570);
    textSetup(signin, "SIGN IN", COURIER, 35, Color(33, 33, 33), 630, 610);

}
//----------------------------------------------------------MOUSE POSTION FUNC-----------------------------------------------
void mousepo(Vector2i& mouseposition)
{
    if (usernamebox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        section = 1;
    }
    if (emailbox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        section = 2;
    }
    if (passbox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        section = 3;
    }
    if (phoneno.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        section = 4;
    }
    if (Age.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        section = 5;
    }
    if (Age.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        section = 5;
    }
    if (balancebox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        section = 6;
    }
    if (AlreadyPressed||IsSignUpPressed)
    {
        if (ButtonSigninBox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
        {
            signinBoxPressed = true;
        }
    }

    if (signinbox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        AlreadyPressed = true;
    }
    if (signupbox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Event::MouseButtonReleased && LeftMouseClicked)
    {
        IsSignUpPressed = true;
    }
    if (emailsigninbox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        p2section = 1;
    }
 
    if (passsigninbox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        p2section = 2;
    }
    if (backbox.box.getGlobalBounds().contains(mouseposition.x, mouseposition.y) && Mouse::isButtonPressed(Mouse::Left))
    {
        textSetup(email, "Email:", COURIER, 45, Color(255, 228, 201), 290, 330);
        textSetup(password, "Password:", COURIER, 45, Color(255, 228, 201), 210, 390);
        AlreadyPressed = false;
        IsSignUpPressed = false;
       
    }
}