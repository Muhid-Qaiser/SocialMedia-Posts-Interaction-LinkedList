#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <ctime>
using namespace std;

class Post
{
public:
    int id;
    string text;
    string timestamp;
    static int auto_inc_id;
    Post *next;

    // * default constructor
    Post()
    {
        this->next = NULL;
    }

    // * parameterized constructor
    Post(string text) : text(text)
    {
        this->next = NULL;

        this->id = auto_inc_id++;

        set_timestamp();
    }

    // * edit post and update timestamp
    void edit_post(string text)
    {
        this->text = text;

        set_timestamp();
    }

    // * sets the timestamp
    void set_timestamp()
    {
        time_t curr_time = time(NULL);
        char time_str[100]; // A buffer to store the formatted time
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&curr_time));
        this->timestamp = time_str;
    }

    // * displays the post
    void display()
    {
        // cout << "\nPost" << endl;
        cout << "-----------------------------------------------\n"
             << endl
             //  << endl
             << "\tID: " << this->id << endl
             << "\tText: " << this->text << endl
             << "\tTimestamp: " << this->timestamp << endl
             //  << endl
             << "\n-----------------------------------------------" << endl;
    }

    // * destructor
    ~Post()
    {
        next = NULL;
        delete next;
    }
};

int Post::auto_inc_id = 1000;

class Feed : public Post
{
    Post *head;
    int size;

public:
    // * constructor
    Feed()
    {
        head = NULL;
        size = 0;
    }

    // * destructor
    ~Feed()
    {
        Post *temp = NULL;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    Post *getNewPost(string data)
    {
        Post *newPost = new Post(data);
        return newPost;
    }

    // * Insertion
    void create_post(string data)
    {
        // Post *newPost = getNewPost(data);
        Post *newPost = new Post(data);

        if (head == NULL)
            head = newPost;

        else
        {
            // * Insertion at head
            newPost->next = head;
            head = newPost;
        }
        size++;
    }

    // * Deletion
    void delete_post()
    {
        if (head == NULL)
        {
            cout << "\nNo Posts Exists!" << endl;
            return;
        }

        int input_id = 0;

        cout << "\nEnter Input ID of Post to Delete: ";
        cin >> input_id;

        if (head->id == input_id)
        {
            // * deletion at head
            Post *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Post *temp = head;
            Post *node_to_delete = NULL;

            // * deletion at value
            while (temp->next->id != input_id)
            {
                if (temp->next->next == NULL)
                {
                    cout << "\nID not Found!" << endl;
                    return;
                }
                temp = temp->next;
            }
            node_to_delete = temp->next;
            temp->next = temp->next->next;

            delete node_to_delete;
        }
        size--;
    }

    void edit_post()
    {
        int post_id = 0;
        string new_text = "";
        bool id_exists = false;
        Post *temp = head;

        cout << "\nEnter Post Id of Post to Edit: ";
        cin >> post_id;
        cin.sync();
        // cin.ignoauto_inc_id

        if (head == NULL)
            cout << "\nList is Empty!\n";

        // * editing at head
        else if (temp->id == post_id)
        {
            id_exists = true;

            cout << "\nEnter New Text: ";
            getline(cin, new_text);

            temp->edit_post(new_text);
        }

        else
        {
            while (temp->next != NULL)
            {
                // * editing at value
                if (temp->next->id == post_id)
                {
                    id_exists = true;

                    cout << "\nEnter New Text: ";
                    getline(cin, new_text);

                    temp->next->edit_post(new_text);

                    Post *edited_post = temp->next;

                    temp->next = temp->next->next;

                    edited_post->next = head;
                    head = edited_post;

                    break;
                }
                temp = temp->next;
            }
        }

        if (!id_exists)
            cout << "\nPost Id Does Not Exist!" << endl;
    }

    void search_with_text()
    {
        string input_text = "";
        Post *temp = head;
        bool flag = false;
        int counter = 1;

        cout << "\nEnter Text to Find Posts: ";
        // cin.sync();
        getline(cin, input_text);

        cout << "\nPosts containing the word, \"" << input_text << "\" : " << endl;

        // * searching entire list
        while (temp != NULL)
        {
            // * if found
            if (temp->text.find(input_text) != string::npos)
            {
                cout << "\nPost Found!\n";
                flag = true;
                cout << "\nPost " << counter++ << endl;
                temp->display();
                cout << endl;
            }
            temp = temp->next;
        }

        if (!flag)
            cout << "\nNo Post containing \"" << input_text << "\" Exists!" << endl;
    }

    void search_with_text(string input_text)
    {
        Post *temp = head;
        bool flag = false;
        int counter = 1;

        // cin.sync();

        cout << "\nPosts containing the word, \"" << input_text << "\" : " << endl;

        // * searching entire list
        while (temp != NULL)
        {
            // * if found
            if (temp->text.find(input_text) != string::npos)
            {
                cout << "\nPost Found!\n";
                cout << "\nPost " << counter++ << ": " << endl;
                flag = true;
                temp->display();
                cout << endl;
            }
            temp = temp->next;
        }

        if (!flag)
            cout << "\nNo Post containing \"" << input_text << "\" Exists!" << endl;
    }

    void display_latest()
    {
        Post *temp = head;
        int counter = 1;

        cout << "\nDisplaying latest post: \n===============================================\n ";

        while (temp != NULL)
        {
            cout << "\nPost " << counter++ << ": " << endl;
            temp->display();
            temp = temp->next;
        }
        cout << endl;
    }

    void recursive_display(Post *p, int counter)
    {
        if (p == NULL)
            return;

        recursive_display(p->next, counter - 1);

        cout << "\nPost " << counter << ": " << endl;
        p->display();
    }

    void display_oldest()
    {
        Post *temp = head;
        cout << "\nDisplaying oldest post: \n===============================================\n ";

        recursive_display(temp, size);
    }

    int get_size() const
    {
        return size;
    }
};

int main()
{
    int delete_num = 0;
    Feed feed;

    cout << "\nFeed Management System " << endl
         << "===============================================\n";

    feed.create_post("Hello World!");
    feed.create_post("How is everyone doing today");

    feed.create_post("I am Hungry");
    feed.create_post("I want to eat Shwarma");
    feed.create_post("I love table tennis");
    feed.create_post("My T.A the Best!");
    feed.create_post("I slept for 13 hrs");
    feed.create_post("I want more sleep");

    feed.create_post("I should be going, see you guys later.");
    feed.create_post("Bye");

    feed.search_with_text();
    // feed.search_with_text("World");
    feed.edit_post();

    feed.display_oldest();

    feed.search_with_text();
    // feed.search_with_text("guys");

    // do
    // {
    //     try
    //     {
    //         cout << "\nEnter Number of Posts to delete: ";
    //         cin >> delete_num;
    //         if (delete_num > feed.get_size())
    //             throw out_of_range("Number of posts to delete must be equal to or less than the Total Number of Posts");
    //     }
    //     catch (out_of_range e)
    //     {
    //         cout << "\nError: " << e.what() << endl;
    //     }
    // } while (delete_num > feed.get_size());

    cout << "\nEnter Number of Posts to delete: ";
    cin >> delete_num;

    while (delete_num > feed.get_size())
    {
        cout << "\n!!Error: Number of posts to delete must be equal to or less than the Total Number of Posts!!" << endl;
        cout << "\nEnter Number of Posts to delete: ";
        cin >> delete_num;
    }

    for (int i = 0; i < delete_num; i++)
        feed.delete_post();

    feed.display_latest();

    cout << "\nExiting....\n\n===============================================\n ";

    return 0;
}