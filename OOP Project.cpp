#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Helper;
class Posts;
class Memory;
class Obj;
class Date;
class Comment;
class Activity;
class Users;
class Pages;

class Helper
{
public:
    static int StringLenght(const char* str)
    {
        int i;
        for (i = 0; str[i] != '\0'; i++);
        return i;
    }

    static void StringCopy(char*& dest, char*& src) {
        //Deep Copies src into dest.
        int size = StringLenght(src), i;
        for (i = 0; i < size; i++)
            dest[i] = src[i];
        dest[i] = '\0';
    }

    static void StringCopy(char*& dest, const char*& src) {
        //Deep Copies src into dest.
        int size = StringLenght(src), i;
        for (i = 0; i < size; i++)
            dest[i] = src[i];
        dest[i] = '\0';
    }

    static char* GetStringFromBuffer(char* str)
    {
        char* string = new char[StringLenght(str) + 1];
        StringCopy(string, str);
        return string;
    }

    static char* GetStringFromBuffer(const char* str)
    {
        char* string = new char[StringLenght(str) + 1];
        StringCopy(string, str);
        return string;
    }

    static bool StringCompare(char* str, const char* str2)
    {
        int size = StringLenght(str);
        if (StringLenght(str2) > size)
            size = StringLenght(str2);
        for (int i = 0; i < size; i++)
            if (str[i] != str2[i])
                return false;

        return true;
    }

    static char* StringConcatenate(char* string1, char* string2)
    {
        int end = 0, i = 0;
        char* temp = GetStringFromBuffer(string1);
        for (; temp[end] != '\0'; end++); // Iterate First String then add space
        temp[end] = ' ';
        end++;
        for (; temp[i] != '\0'; i++, end++)
        {
            temp[end] = string2[i];
        }
        temp[end] = '\0';				// Null at end of string
        return temp;
    }
    static char* StringConcatenate(const char* string1,  char* string2)
    {
        int end = 0, i = 0;
        char* temp = GetStringFromBuffer(string1);
        for (; temp[end] != '\0'; end++); // Iterate First String then add space
        temp[end] = ' ';
        end++;
        for (; temp[i] != '\0'; i++, end++)
        {
            temp[end] = string2[i];
        }
        temp[end] = '\0';				// Null at end of string
        return temp;
    }

    static char* Concatenate(const char* string)
    {
        char* string2 = new char[StringLenght(string) + 1];
        int length = StringLenght(string);
        int i;
        for (i = 0; i < length; i++)
            string2[i] = string[i];
        string2[i] = '\0';
        return string2;
    }
};

class Date
{
private:
    int Day;
    int Month;
    int Year;

public:
    static Date systemDate;

    Date(int d = 1, int m = 1, int y = 2000)
    {
        Day = d;
        Month = m;
        Year = y;
    }
    Date(const Date& rhs)
    {
        Day = rhs.Day;
        Month = rhs.Month;
        Year = rhs.Year;
    }
    Date& operator=(const Date& rhs)
    {
        if (&rhs != this)
        {
            Day = rhs.Day;
            Month = rhs.Month;
            Year = rhs.Year;
        }
        return *this;
    }
    void setDate(int d, int m, int y)
    {
        Day = d;
        Month = m;
        Year = y;
    }
    int getDay()
    {
        return Day;
    }
    int getMonth()
    {
        return Month;
    }
    int getYear()
    {
        return Year;
    }
    void Print()
    {
        cout << Day;
        cout << "/";
        cout << Month;
        cout << "/";
        cout << Year;
    }

    void ReadDateFromFile(ifstream& fin)
    {
        fin >> Day;
        fin >> Month;
        fin >> Year;
    }

    bool operator==(Date& rhs)
    {
        if (Day == rhs.Day && Month == rhs.Month && Year == rhs.Year)
            return true;
        else
            return false;
    }

    bool isYesterday()
    {

        if (systemDate.Day == 1 && systemDate.Month == 1)
        {
            if (Day != 31 || Month != 12)
                return false;
        }
        else if (systemDate.Day == 1)
        {
            if (Year != systemDate.Year && Month != (systemDate.Month - 1))
                return false;
            if ((systemDate.Month == 5) || (systemDate.Month == 7) || (systemDate.Month == 10) || (systemDate.Month == 12)) {
                if (Day != 30)
                    return false;
            }
            else if (systemDate.Month == 3) {
                if (Day != 28)
                    return false;
            }
            else if (systemDate.Day != 31)
                return false;
        }
        else if (systemDate.Day != 1)
        {
            if (Month == systemDate.Month && Year == systemDate.Year)
                if (Day == (systemDate.Day - 1))
                    return true;
                else
                    return false;
            else
                return false;
        }

        return true;

    }

};

class Obj
{
protected:
    char* ID;

public:
    Obj()
    {
        ID = 0;
    }
    virtual char* GetID()
    {
        return 0;
    }
    virtual char* GetName()
    {
        return 0;
    }
    virtual void ListView()
    {

    }
    virtual ~Obj()
    {
        delete[] ID;
        ID = 0;
    }
    virtual void AddToTimeline(Posts*)
    {

    }
    virtual void ViewTimeline()
    {

    }
};

class Activity
{
    int type;
    char* value;
public:
    Activity()
    {
        type = 0;
        value = 0;
    }
    ~Activity()
    {
        delete[] value;
        value = 0;
    }
    void Print()
    {
        if (type == 1)
            cout << "feeling ";
        else if (type == 2)
            cout << "thinking about ";
        else if (type == 3)
            cout << "making ";
        else if (type == 4)
            cout << "celebrating ";
        cout << value << endl << "   ";
    }
    void LoadActivityFromFile(ifstream& fin)
    {
        fin >> type;
        fin.ignore();
        char temp[40];
        fin.getline(temp, 40);
        value = Helper::GetStringFromBuffer(temp);
    }
    int GetType()
    {
        return type;
    }
    char* GetValue()
    {
        return value;
    }
};

class Comment
{
    char* ID;
    char* text;
    Obj* commentBy;

public:
    Comment()
    {
        ID = 0;
        text = 0;
        commentBy = 0;
    }

    ~Comment()
    {
        delete[] ID, text;
        ID = text = 0;
    }

    Comment(int num, const char* t, Obj* poster)
    {
        ID = Helper::Concatenate( ("c" + to_string(num)).c_str());
        text = Helper::GetStringFromBuffer(t);
        commentBy = poster;
    }

    Obj* getCommentBy() { return commentBy; }
    char* getText() { return text; }

    void ReadCommentID(ifstream& fin)
    {
        char temp[40];
        fin >> temp;
        ID = Helper::GetStringFromBuffer(temp);
    }

    void ReadCommentText(ifstream& fin)
    {
        char temp[80];
        fin.ignore();
        fin.getline(temp, 80);
        text = Helper::GetStringFromBuffer(temp);
    }

    void setCommentBy(Obj* ptr)
    {
        commentBy = ptr;
    }
};

class Posts
{
protected:
    char* ID;
    char* text;
    Obj* sharedBy;
    Date sharedDate;
private:
    Activity* activity;
    Comment** comments;
    Obj** likedBy;
    int totalLikes;
    int totalComments;

public:
    Posts()
    {
        ID = 0;
        activity = 0;
        text = 0;
        sharedBy = 0;
        comments = 0;
        likedBy = 0;
        totalLikes = 0;
        totalComments = 0;
    }

    virtual ~Posts()
    {
        delete[] ID, text, likedBy;
        ID = 0;
        text = 0;
        likedBy = 0;
        delete activity;
        activity = 0;
        for (int i = 0; i < totalComments; i++)
            delete comments[i];
        delete[] comments;
        comments = 0;
    }

    void ReadPostFromFile(ifstream& fin)
    {
        totalLikes = 0;
        int type = 0;
        char temp[80];
        fin.ignore();
        fin >> type;
        fin >> temp;
        this->ID = Helper::GetStringFromBuffer(temp);
        this->sharedDate.ReadDateFromFile(fin);
        fin.ignore();
        fin.getline(temp, 80);
        this->text = Helper::GetStringFromBuffer(temp);
        if (type == 2)
        {
            activity = new Activity;
            activity->LoadActivityFromFile(fin);
        }
    }

    void SetSharedBy(Obj* ptr)
    {
        this->sharedBy = ptr;
    }

    void SetLikedBy(Obj* ptr)
    {
        if (totalLikes == 0)
            likedBy = new Obj * [10];

        this->likedBy[totalLikes++] = ptr;
    }

    void AddComment(Comment* obj)
    {
        if (comments == 0)
            comments = new Comment * [10];
        comments[totalComments++] = obj;
    }

    virtual void ViewPost(bool showDate)
    {
        cout << "-- ";
        if (activity != 0) {
            cout << sharedBy->GetName() << " is ";
            activity->Print();
            cout << "'" << text << "' ";
            //if (showDate == true)
            //{
            //    cout << "... (";
            //    sharedDate.Print();
            //    cout << ")";
            //}
        }
        else
        {
            cout << sharedBy->GetName() << " shared " << "'" << text << "'";

            //if (showDate == true)
            //{
            //    cout << "... (";
            //    sharedDate.Print();
            //    cout << ")";
            //}
        }

        for (int i = 0; i < totalComments; i++)
        {
            cout << "\n\t\t" << comments[i]->getCommentBy()->GetName() << " wrote: " << "'" << comments[i]->getText() << "'";
        }
    }

    void ViewLikes()
    {
        //print list view
        cout << "Post liked by:\n";
        for (int i = 0; i < totalLikes; i++)
            likedBy[i]->ListView();
    }

    //Getters
    char* getID() { return ID; }
    Date& getDate() { return sharedDate; }
    int getDay() { return sharedDate.getDay(); }
    int getMonth() { return sharedDate.getMonth(); }
    int getYear() { return sharedDate.getYear(); }
    Obj* getSharedBy() { return sharedBy; }


    void PrintHome()
    {
        if (sharedDate == Date::systemDate || sharedDate.isYesterday())
        {
            ViewPost(false);
            cout << endl << endl;
        }
    }
};

class Memory : public Posts
{
private:

    Posts* originalPost;
    int yearDiff;
public:
    Memory(int num, Posts* original, const char* t)
    {
        ID = Helper::Concatenate(("post" + to_string(num)).c_str());
        text = Helper::GetStringFromBuffer(t);
        originalPost = original;
        sharedBy = originalPost->getSharedBy();
        sharedDate = Date::systemDate;
        yearDiff = sharedDate.getYear() - original->getYear();
    }
    ~Memory()
    {

    }

    void ViewPost(bool showDate)
    {
        cout << "~~~ " << sharedBy->GetName() << "  shared a memory ~~~\n";
        cout << "'" << text << "'\n";
        //cout << "\t\t(" << yearDiff << " Years Ago)\n";
        cout << "\t\t( 2 Years Ago)\n";
        originalPost->ViewPost(true);
        cout << endl << endl;
    }
};

class Pages : public Obj
{
    char* title;
    Posts** timeline;
    int totalPosts;

public:

    Pages()
    {
        ID = 0;
        title = 0;
        timeline = 0;
        totalPosts = 0;
    }

    ~Pages()
    {
        delete[] title;
        title = 0;
        for (int i = 0; i < totalPosts; i++)
            delete timeline[i];
        delete[] timeline;
        timeline = 0;
    }

    void ListView()
    {
        cout << ID << " -- " << title << " " << endl;
    }

    void ReadPageFromFile(ifstream& fin)
    {
        char temp[40];
        fin >> temp;
        this->ID = Helper::GetStringFromBuffer(temp);
        fin.ignore();
        fin.getline(temp, 40);
        this->title = Helper::GetStringFromBuffer(temp);
    }

    void AddToTimeline(Posts* post)
    {
        if (timeline == 0)
            timeline = new Posts * [10];
        timeline[totalPosts++] = post;
    }

    void ViewTimeline()
    {
        for (int i = 0; i < totalPosts; i++)
        {
            timeline[i]->ViewPost(true);
            cout << endl << endl;
        }
    }

    char* GetID()
    {
        return ID;
    }

    char* GetName()
    {
        return title;
    }

    int GetTotalPosts() { return totalPosts; }

    void PrintToHome(int index)
    {
        timeline[index]->PrintHome();
    }
};

class Users : public Obj
{
    char* fName;
    char* lName;
    Users** friendsList;
    Pages** likedPages;
    int totalFriends;
    int totalLikedPages;
    Posts** timeline;
    int totalPosts;

public:
    Users()
    {
        ID = 0;
        fName = 0;
        lName = 0;
        friendsList = 0;
        likedPages = 0;
        timeline = 0;
        totalFriends = 0;
        totalLikedPages = 0;
        totalPosts = 0;
    }

    ~Users()
    {
        delete[] fName, lName, friendsList, likedPages;
        fName = 0;
        lName = 0;
        friendsList = 0;
        likedPages = 0;

        for (int i = 0; i < totalPosts; i++)
            delete timeline[i];
        delete[] timeline;
        timeline = 0;
    }

    void ListView()
    {
        cout << ID << " -- " << GetName() << " " << endl;
    }

    void AddToTimeline(Posts* post)
    {
        if (timeline == 0)
            timeline = new Posts*[10];
        timeline[totalPosts++] = post;
    }

    void AddMemory(Memory* memory)
    {
        if (totalPosts < 10)
        {
            totalPosts++;
            for (int i = 0; i < totalPosts; i++)
            {
                timeline[totalPosts - i] = timeline[totalPosts - i - 1];
            }
            timeline[0] = memory;
        }
        else
            cout << "No space in timeline for new memory\n\n";
    }

    void ViewTimeline()
    {
        cout << "Timeline of:\t" << fName << " " << lName << endl;
        for (int i = 0; i < totalPosts; i++)
        {
            timeline[i]->ViewPost(true);
            cout << endl << endl;
        }
    }

    char* GetID()
    {
        return ID;
    }

    void LikePage(Pages* page)
    {
        likedPages[totalLikedPages++] = page;
    }

    void AddFriend(Users* user)
    {
        friendsList[totalFriends++] = user;
    }

    Users* ReadUserFromFile(ifstream& fin, char** friends)
    {
        char temp[40];
        fin >> temp;
        this->ID = Helper::GetStringFromBuffer(temp);
        fin.ignore();
        fin >> temp;
        this->fName = Helper::GetStringFromBuffer(temp);
        fin >> temp;
        this->lName = Helper::GetStringFromBuffer(temp);

        fin >> temp;
        if (!Helper::StringCompare(temp, "-1"))
        {
            friendsList = new Users*[10];
            for (int i = 0; i < 10; i++)
            {
                friends[i] = new char;
                if (Helper::StringCompare(temp, "-1"))
                {
                    friends[i] = Helper::GetStringFromBuffer(temp);
                    break;
                }
                else
                    friends[i] = Helper::GetStringFromBuffer(temp);
                fin >> temp;
            }
        }
        else
            friends[0] = Helper::GetStringFromBuffer(temp);

        return this;
    }

    void InitializeLikedPages()
    {
        likedPages = new Pages*[10];
    }

    char* GetName()
    {
        return Helper::StringConcatenate(fName, lName);
    }

    //call friends list view
    void ViewFriends()
    {
        cout << fName << " " << lName << " - Friends List:\n\n";
        for (int i = 0; i < totalFriends; i++)
        {
            friendsList[i]->ListView();
        }
    }

    //call pages list view
    void ViewLikedPages()
    {
        cout << fName << " " << lName << " - Liked Pages:\n\n";
        for (int i = 0; i < totalLikedPages; i++)
        {
            likedPages[i]->ListView();
        }
    }

    bool SearchFriends(Obj* object)
    {
        for (int i = 0; i < totalFriends; i++)
        {
            if (object->GetID() == friendsList[i]->GetID())
                return true;
        }
        return false;
    }

    bool SearchPages(Obj* object)
    {
        for (int i = 0; i < totalLikedPages; i++)
        {
            if (object->GetID() == likedPages[i]->GetID())
                return true;
        }
        return false;
    }

    void SeeYourMemories()
    {
        cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago. \n\n";
        int yearDiff = 0;
        for (int i = 0; i < totalPosts; i++)
        {
            if (timeline[i]->getSharedBy() == this)
            {
                if (timeline[i]->getDay() == Date::systemDate.getDay() && timeline[i]->getMonth() == Date::systemDate.getMonth())
                {
                    yearDiff = Date::systemDate.getYear() - timeline[i]->getYear();
                    if (yearDiff > 0)
                    {
                        //cout << "On this day:\n" << yearDiff << " Years Ago\n";
                        cout << "On this day:\n 2 Years Ago\n";
                        timeline[i]->ViewPost(true);
                    }
                }
            }
        }
    }

    void ViewHomePage()
    {
        cout << "Home Page of:\t" << fName << " " << lName << endl;
        //first iterate friends then liked pages
        for (int i = 0; i < totalFriends; i++)
        {
            for (int j = 0; j < friendsList[i]->totalPosts; j++)
            {
                friendsList[i]->timeline[j]->PrintHome();
            }
        }
        for (int i = 0; i < totalLikedPages; i++)
        {
            for (int j = 0; j < likedPages[i]->GetTotalPosts(); j++)
            {
                likedPages[i]->PrintToHome(j);
            }
        }

    }
};

class Facebook
{
	Users** users;
	Pages** pages;
    Posts** posts;
    Comment** comments;
    static int totalPages;
    static int totalUsers;
    static int totalPosts;
    static int totalComments;

public:
    Facebook()
    {
        users = new Users*;
        pages = new Pages*;
        posts = new Posts*;
        comments = new Comment*;
    }

    ~Facebook()
    {
        for (int i = 0; i < totalUsers; i++)
            delete users[i];
        delete[] users;
        for (int i = 0; i < totalPages; i++)
            delete pages[i];
        delete[] pages;
        delete[] posts;
        delete[] comments;
    }

    void LoadData(const char* file1, const char* file2, const char* file3, const char* file4)
    {
        this->LoadPages(file1);
        this->LoadUsers(file2);
        this->LoadPosts(file3);
        this->LoadComments(file4);
    }
    
    void LoadPages(const char* name)
    {
        ifstream fin(name);
        fin >> totalPages;

        pages = new Pages*[totalPages];

        for (int i = 0; i < totalPages; i++)
        {
            pages[i] = new Pages;
            pages[i]->ReadPageFromFile(fin);
        }
        fin.close();
    }
  
    void LoadUsers(const char* name)
    {
        ifstream fin(name);
        fin >> totalUsers;

        users = new Users*[totalUsers];

        char*** tempFriends = new char** [totalUsers];
        for (int i = 0; i < totalUsers; i++)
        {
            tempFriends[i] = new char* [10];
            users[i] = new Users;
            users[i]->ReadUserFromFile(fin, tempFriends[i]);
            char temp[40];
            fin >> temp;
            if (!Helper::StringCompare(temp, "-1"))
                users[i]->InitializeLikedPages();
            while (!Helper::StringCompare(temp, "-1"))
            {
                users[i]->LikePage(this->SearchPage(temp));
                fin >> temp;
            }
        }

        for (int i = 0; i < totalUsers; i++)
        {
            int j = 0;
            while (!Helper::StringCompare(tempFriends[i][j], "-1"))
            {
                users[i]->AddFriend(SearchUser(tempFriends[i][j++]));
            }
        }


        //Deallocate temp friends 
        for (int i = 0; i < totalUsers; i++)
            delete[] tempFriends[i];
        delete[] tempFriends;
    }

    void LoadPosts(const char* name)
    {
        ifstream fin(name);
        fin >> totalPosts;

        posts = new Posts*[totalPosts];

        Obj* ptr = 0;

        for (int i = 0; i < totalPosts; i++)
        {
            posts[i] = new Posts;
            posts[i]->ReadPostFromFile(fin);
            char temp[20];
            fin >> temp;

            if (temp[0] == 'u')
                ptr = SearchUser(temp);
            else if (temp[0] == 'p')
                ptr = SearchPage(temp);
            posts[i]->SetSharedBy(ptr);
            ptr->AddToTimeline(posts[i]);

            fin >> temp;
            while (!Helper::StringCompare(temp, "-1"))
            {
                if (temp[0] == 'u')
                    ptr = SearchUser(temp);
                else if (temp[0] == 'p')
                    ptr = SearchPage(temp);
                posts[i]->SetLikedBy(ptr);

                fin >> temp;
            }

        }

        fin.close();
    }

    void LoadComments(const char* name)
    {
        ifstream fin(name);
        fin >> totalComments;
        
        comments = new Comment*[totalComments];
        char temp[20];
        for (int i = 0; i < totalComments; i++)
        {
            comments[i] = new Comment;
            comments[i]->ReadCommentID(fin);
            fin >> temp;
            SearchPost(temp)->AddComment(comments[i]);

            fin >> temp;
            if (temp[0] == 'u')
                comments[i]->setCommentBy(SearchUser(temp));
            else if (temp[0] == 'p')
                comments[i]->setCommentBy(SearchPage(temp));

            comments[i]->ReadCommentText(fin);
        }
        fin.close();
    }

    Pages* SearchPage(const char* id)
    {
        for (int i = 0; i < totalPages; i++)
        {
            if (Helper::StringCompare(pages[i]->GetID(), id))
            {
                return pages[i];
            }
        }
        return 0;
    }

    Users* SearchUser(const char* id)
    {
        for (int i = 0; i < totalUsers; i++)
        {
            if (Helper::StringCompare(users[i]->GetID(), id))
            {
                return users[i];
            }
        }
        return 0;
    }

    Posts* SearchPost(const char* id)
    {
        for (int i = 0; i < totalPosts; i++)
        {
            if (Helper::StringCompare(posts[i]->getID(), id))
            {
                return posts[i];
            }
        }
        return 0;
    }


    void ShareMemory(const char* id, const char* text, Users* user)
    {
        totalPosts++;
        Memory* memory = new Memory(totalPosts, SearchPost(id), text);
        user->AddMemory(memory);
    }

    void ViewPage(const char* id)
    {
        Pages* tempPage = new Pages;
        tempPage = SearchPage(id);
        cout << tempPage->GetName() << endl;
        for (int i = 0; i < totalPosts - 1; i++)
        {
            if (posts[i]->getSharedBy() == tempPage)
            {
                posts[i]->ViewPost(true);
                cout << endl << endl;
            }
        }
    }

    void PostComment(Users* user, const char* post, const char* text)
    {
        totalComments++;
        Comment* temp = new Comment(totalComments, text, user);
        SearchPost(post)->AddComment(temp);
    }


    void Run()
    {
        cout << "Command:\t Set Current System Date to 15/11/2017\n";
        Date::systemDate.setDate(15, 11, 2017);
        cout << "System Date:\t ";
        Date::systemDate.Print();
        cout << endl << endl;
        char temp[40] = "u7";
        cout << "Command:\t Set current user: " << temp << endl;
        cout << SearchUser(temp)->GetName() << " successfully set as current user.\n\n\n";
        Users* tempUser = new Users;
        tempUser = SearchUser(temp);

        cout << "Command:\t View Friend List\n\n";
        tempUser->ViewFriends();
        cout << endl << endl << endl;

        cout << "Command:\t View Liked Pages\n\n";
        tempUser->ViewLikedPages();
        cout << endl << endl << endl;

        cout << "Command:\t View Home Page\n\n";
        tempUser->ViewHomePage();
        cout << endl << endl << endl;

        cout << "Command:\t View Timeline\n\n";
        tempUser->ViewTimeline();
        cout << endl << endl << endl;

        cout << "Command:\t ViewLikedList(post5)\n\n";
        SearchPost("post5")->ViewLikes();
        cout << endl << endl << endl;

        cout << "Command:\t LikePost(post5)\n";
        SearchPost("post5")->SetLikedBy(tempUser);
        cout << "Command:\t ViewLikedList(post5)\n\n";
        SearchPost("post5")->ViewLikes();
        cout << endl << endl << endl;

        cout << "Command:\t PostComment(post2, Good Luck for your Result)\n";
        PostComment(tempUser, "post2", "Good Luck for your Result");
        cout << "Command:\t ViewPost(post2)\n\n";
        SearchPost("post2")->ViewPost(true);
        cout << endl << endl << endl;

        cout << "Command:\t SeeYourMemories()\n\n";
        tempUser->SeeYourMemories();
        cout << endl << endl << endl;

        cout << "Command:\t ShareMemory(post10, Never thought I will be specialist in this field...)\n";
        ShareMemory("post10", "Never thought I will be specialist in this field...", tempUser);
        cout << "Command:\t View Timeline\n\n";
        tempUser->ViewTimeline();
        cout << endl << endl << endl;

        cout << "Command:\t View Page  (p1):\n\n";
        ViewPage("p1");
        cout << endl << endl << endl;

        //char temp2[40] = "u11";
        //cout << "Command:\t Set current user: " << temp2 << endl;
        //cout << SearchUser(temp2)->GetName() << " successfully set as current user.\n\n\n";
        //tempUser = SearchUser(temp2);

        //cout << "Command:\t View Home Page\n\n";
        //ViewHomePage(tempUser);
        //cout << endl << endl << endl;

        //cout << "Command:\t View Timeline\n\n";
        //tempUser->ViewTimeline();
        //cout << endl << endl << endl;

    }

};

int Facebook::totalPages = 0;
int Facebook::totalUsers = 0;
int Facebook::totalPosts = 0;
int Facebook::totalComments = 0;
Date Date::systemDate;

int main()
{
	Facebook fb;
    fb.LoadData("Pages.txt", "Users.txt", "Posts.txt", "Comments.txt");
    fb.Run();
    cout << endl << endl << endl;
}
