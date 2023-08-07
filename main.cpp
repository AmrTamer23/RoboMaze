#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include<queue>

using namespace std;
using namespace sf;

const int SIZE = 10;
const int CELL_SIZE = 90;
float delay = 0;
int animation = 0;
int visitedc = 0;
int walls = 0;
float deltatime=0;
bool moving=0;
Clock game;
Clock gameclock;
string arrayOfInteractions[12];
string arrayOfInteractions2[12];
string path ="";
bool Interacting = false;
bool clicked = false;


struct reminder
{
private:
    Vector2f frameScale;
    Sprite frameSprite;
    Texture frameTexture;

    Font arcadeClassic;
    string final_string;
    string displayed_text;
    Text textToBeDisplayed;

    Text pressSpaceToSkip;
    string player_name;
    bool aborted = false;

    void setInteractions2(string arr[])
    {
        arr[0] = "Something is wrong!, \n make it agian";
        arr[1] = "you still doing that shit! \nduhhhhh!";
        arr[2] = "SEE HOW DUMP IS HE! HAHAHAHA";
        arr[3] = "The maze is not logically set\nAll cells must be reachable,\ntry to confuse me.";
        arr[4] = "something is not connected.";
        arr[5] = "let me see your best \nat building it again.";
        arr[6] = "are you good at \n building mazes? ,i don't think so.";
        arr[7] = "There is UnReachable Path.";
        arr[8] = "you built it wrong! ";
        arr[9] = "";
        arr[10] = "";
        arr[11] = "";
    }

public:
    int no_of_interactions = 6;
    float timer_per_letter = 0.1;

    bool finishedInteracting = false;
    bool deletingWindow = false;
    bool isActive = false;

    void interactionSetProp(string interactions[],float xPos, float yPos)
    {
        text_index = 0;
        textTimer = 0.1;
        pauseTimer = 2.5;
        aborted = false;
        deletingWindow = false;
        finishedInteracting = false;
        xpos = xPos;
        ypos = yPos;
        setInteractions2(interactions);

        // loads textures
        frameTexture.loadFromFile(path + "images/textbox2_1.png");
        frameSprite.setTexture(frameTexture);
        frameSprite.setPosition(xPos, yPos);
        textToBeDisplayed.setPosition(frameSprite.getPosition().x - 200, frameSprite.getPosition().y - 75);
        textToBeDisplayed.setFillColor(Color::Black);
        frameSprite.setOrigin(250, 250);

        pressSpaceToSkip.setPosition(190, 633);
        pressSpaceToSkip.setScale(2, 2);

        // set initial scales
        frameSprite.setScale(0, 0);

        textToBeDisplayed.setScale(0.8, 0.8);

        // set final scales
        frameScale = {1.29, 1.29};

        arcadeClassic.loadFromFile(path + "fonts/Comicaboom.otf");
        textToBeDisplayed.setFont(arcadeClassic);
        //pressSpaceToSkip.setFont(arcadeClassic);
        //pressSpaceToSkip.setString("Press Space To Skip");
        displayed_text = "";

        // takes a random interaction out of the interactions array
        int randomNumb = rand() % no_of_interactions;
        final_string ="\n" + interactions[randomNumb];
        textToBeDisplayed.setString(displayed_text);
    }

private:
    int text_index = 0;
    float textTimer = 0.1;
    float pauseTimer = 0.2;
    int flutter_timer = 20;
    bool isSkipTextShown = true;
    // properties set by user using set prop function
    float xpos;
    float ypos;
    string inter_arr[100];

public:
    // update functions: gradually scales window, then gradually scales icon, then gradually shows text
    void update(float deltatime, RenderWindow &window)
    {
        float scale_offset = 2;
        float descale_offset = 2;

        if(finishedInteracting)
        {
            cout << "finished interacting\n";
        }
        else
            cout << "not finished interacting\n";

        // if the window isnt big enough yet, it gets scaled
        if (frameSprite.getScale().x < frameScale.x and frameSprite.getScale().y < frameScale.y and !deletingWindow and !aborted)
        {
            frameSprite.setScale({frameSprite.getScale().x + scale_offset * deltatime, frameSprite.getScale().y + scale_offset * deltatime});
        }

        // if both window is scaled, we start displaying the text gradually
        else
        {
            // if not all of string have been displayed
            if (text_index < final_string.length() and !aborted)
            {
                if (textTimer <= 0)
                {
                    displayed_text = displayed_text + final_string[text_index];
                    textToBeDisplayed.setString(displayed_text);
                    text_index++;
                    textTimer = timer_per_letter;
                }
                else
                    textTimer -= deltatime;
            }
            // if all has been displayed, starts timer, and when it ends, it destroys the window
            else
            {
                if (pauseTimer <= 0 or aborted)
                {
                    deletingWindow = true;
                    // if not , plays reverse animation for shrinking
                    if (frameSprite.getScale().x > 0 and frameSprite.getScale().y > 0 and !finishedInteracting)
                    {
                        frameSprite.setScale({frameSprite.getScale().x - descale_offset * deltatime, frameSprite.getScale().y - descale_offset * deltatime});
                        textToBeDisplayed.setScale(0, 0);
                    }
                    // if finished shrinking, destroys and marks the bool as true for external use
                    else if (frameSprite.getScale().x <= 0 or frameSprite.getScale().y <= 0)
                    {
                        frameSprite.setScale(0, 0);
                        textToBeDisplayed.setScale(0, 0);
                        finishedInteracting = true;
                    }
                }
                else
                    pauseTimer -= deltatime;
            }
        }
    }
    void draw(RenderWindow& window)
    {
        if (!finishedInteracting)
        {
            window.draw(frameSprite);
            window.draw(textToBeDisplayed);
        }
    }

    void abort()
    {
        aborted = true;
    }
} seeked;

struct interactionWindow
{
private:
    Vector2f frameScale;
    Sprite frameSprite;
    Texture frameTexture;

    Font arcadeClassic;
    string final_string;
    string displayed_text;
    Text textToBeDisplayed;

    Text pressSpaceToSkip;
    string player_name;
    bool aborted = false;

    void setInteractions(string arr[])
    {
        arr[0] = "WHO THE HELL ARE YOU, SIR? ,\n by the way let me introduce myself";
        arr[1] = "My Name is The Labyrinthian,unlike my name says\nyou can't make me get lost,\nMy developers Abdelrahman and Amr \nmade sure of that, so good luck with that.";
        arr[2] = "you still here , duhhhhh boring! \ngo and do something.";
    }

public:
    int no_of_interactions = 6;
    float timer_per_letter = 0.1;

    bool finishedInteracting = false;
    bool deletingWindow = false;
    bool isActive = false;

    void interactionSetProp(string interactions[],float xPos, float yPos,int index)
    {
        text_index = 0;
        textTimer = 0.1;
        pauseTimer = 2.5;
        aborted = false;
        deletingWindow = false;
        finishedInteracting = false;
        xpos = xPos;
        ypos = yPos;
        setInteractions(interactions);

        // loads textures
        frameTexture.loadFromFile(path + "images/textbox2_1.png");
        frameSprite.setTexture(frameTexture);
        frameSprite.setPosition(xPos, yPos);
        textToBeDisplayed.setPosition(frameSprite.getPosition().x - 270, frameSprite.getPosition().y - 75);
        textToBeDisplayed.setFillColor(Color::Black);
        frameSprite.setOrigin(250, 250);

        pressSpaceToSkip.setPosition(190, 633);
        pressSpaceToSkip.setScale(2, 2);

        // set initial scales
        frameSprite.setScale(0, 0);

        textToBeDisplayed.setScale(0.8, 0.8);

        // set final scales
        frameScale = {1.9, 1.9};

        arcadeClassic.loadFromFile(path + "fonts/Comicaboom.otf");
        textToBeDisplayed.setFont(arcadeClassic);
        pressSpaceToSkip.setFont(arcadeClassic);
        pressSpaceToSkip.setString("Press Space To Skip");
        displayed_text = "";

        // takes a random interaction out of the interactions array
        final_string ="\n" + interactions[index];
        textToBeDisplayed.setString(displayed_text);
    }

private:
    int text_index = 0;
    float textTimer = 0.1;
    float pauseTimer = 2.5;
    int flutter_timer = 20;
    bool isSkipTextShown = true;
    // properties set by user using set prop function
    float xpos;
    float ypos;
    string inter_arr[100];

public:
    // update functions: gradually scales window, then gradually scales icon, then gradually shows text
    void update(float deltatime, RenderWindow &window)
    {
        float scale_offset = 2;
        float descale_offset = 2;

        // if the window isnt big enough yet, it gets scaled
        if (frameSprite.getScale().x < frameScale.x and frameSprite.getScale().y < frameScale.y and !deletingWindow and !aborted)
        {
            frameSprite.setScale({frameSprite.getScale().x + scale_offset * deltatime, frameSprite.getScale().y + scale_offset * deltatime});
        }

        // if both window is scaled, we start displaying the text gradually
        else
        {
            // if not all of string have been displayed
            if (text_index < final_string.length() and !aborted)
            {
                if (textTimer <= 0)
                {
                    displayed_text = displayed_text + final_string[text_index];
                    textToBeDisplayed.setString(displayed_text);
                    text_index++;
                    textTimer = timer_per_letter;
                }
                else
                    textTimer -= deltatime;
            }
            // if all has been displayed, starts timer, and when it ends, it destroys the window
            else
            {
                if (pauseTimer <= 0 or aborted)
                {
                    deletingWindow = true;
                    // if not , plays reverse animation for shrinking
                    if (frameSprite.getScale().x > 0 and frameSprite.getScale().y > 0 and !finishedInteracting)
                    {
                        frameSprite.setScale({frameSprite.getScale().x - descale_offset * deltatime, frameSprite.getScale().y - descale_offset * deltatime});
                        textToBeDisplayed.setScale(0, 0);
                    }
                    // if finished shrinking, destroys and marks the bool as true for external use
                    else if (frameSprite.getScale().x <= 0 or frameSprite.getScale().y <= 0)
                    {
                        frameSprite.setScale(0, 0);
                        textToBeDisplayed.setScale(0, 0);
                        finishedInteracting = true;
                    }
                }
                else
                    pauseTimer -= deltatime;
            }
        }
    }
    void draw(RenderWindow& window)
    {
        if (!finishedInteracting)
        {
            // flutters the press to skip text
            if (!aborted)
            {
                if (flutter_timer <= 0)
                {
                    if (isSkipTextShown)
                    {
                        isSkipTextShown = false;
                    }
                    else
                        isSkipTextShown = true;

                    flutter_timer = 20;
                }
                else
                {
                    if (isSkipTextShown)
                    {
                        window.draw(pressSpaceToSkip);
                    }
                    flutter_timer -= deltatime;
                }
            }

            window.draw(frameSprite);
            window.draw(textToBeDisplayed);
        }
    }

    void abort()
    {
        aborted = true;
    }
} interactionwindow1,interactionWindow2,interactionWindow3;

class Maze
{
public:

    Maze(RenderWindow& window) : window(window)
    {
        maze.resize(SIZE, vector<bool>(SIZE, false));
        if (!wall.loadFromFile("images/wall.png"))
        {
            cout << "Failed to load wall texture." << endl;
            return;
        }
        if (!path.loadFromFile("images/path.png"))
        {
            cout << "Failed to load path texture." << endl;
            return;
        }
        if (!startPointTex.loadFromFile("images/startpoint.png"))
        {
            cout << "Failed to load start point texture." << endl;
            return;
        }
        if (!endPointTex.loadFromFile("images/endpoint.png"))
        {
            cout << "Failed to load end point texture." << endl;
            return;
        }
        startPos = Vector2i(0, 0);
        endPos = Vector2i(SIZE - 1, SIZE - 1);
    }

    void handleMouseClick(Vector2i mousePos)
    {
        int col = mousePos.x / CELL_SIZE;
        int row = mousePos.y / CELL_SIZE;
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE)
        {
            maze[row][col] = !maze[row][col];
        }
        if(maze[row][col])
        {
            walls++;
        }
        else
        {
            walls--;
        }
    }

    void draw()
    {
        float scaleFactorWall = float(CELL_SIZE) / float(wall.getSize().x);
        float scaleFactorPath = float(CELL_SIZE) / float(path.getSize().x);
        float scaleFactorStartEnd = float(CELL_SIZE) / float(startPointTex.getSize().x);

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                Sprite cell;
                cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);


                if (maze[i][j])
                {
                    cell.setTexture(wall);
                    cell.setScale(scaleFactorWall, scaleFactorWall);
                }
                else
                {
                    cell.setTexture(path);
                    cell.setScale(scaleFactorPath, scaleFactorPath);
                }

                window.draw(cell);
            }
        }
    }

    // if it's wall or not
    bool isWall(int row, int col) const
    {
        return maze[row][col];
    }

    vector<Vector2i> findShortestPath(const Vector2i& startPos, const Vector2i& endPos)
    {
        vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false));
        vector<vector<Vector2i>> parent(SIZE, vector<Vector2i>(SIZE, Vector2i(-1, -1)));

        queue<Vector2i> q;
        q.push((Vector2i)startPos);
        visited[startPos.y][startPos.x] = true;

        while (!q.empty())
        {
            Vector2i current = q.front();
            q.pop();

            if (current == endPos)
                break;

            int row = current.y;
            int col = current.x;


            if (row > 0 && !maze[row - 1][col] && !visited[row - 1][col])
            {
                q.push(Vector2i(col, row - 1));
                visited[row - 1][col] = true;
                parent[row - 1][col] = current;
            }
            if (row < SIZE - 1 && !maze[row + 1][col] && !visited[row + 1][col])
            {
                q.push(Vector2i(col, row + 1));
                visited[row + 1][col] = true;
                parent[row + 1][col] = current;
            }
            if (col > 0 && !maze[row][col - 1] && !visited[row][col - 1])
            {
                q.push(Vector2i(col - 1, row));
                visited[row][col - 1] = true;
                parent[row][col - 1] = current;
            }
            if (col < SIZE - 1 && !maze[row][col + 1] && !visited[row][col + 1])
            {
                q.push(Vector2i(col + 1, row));
                visited[row][col + 1] = true;
                parent[row][col + 1] = current;
            }
        }

        vector<Vector2i> shortestPath;
        Vector2i current = endPos;
        while (current != (Vector2i)startPos)
        {
            shortestPath.push_back(current);
            current = parent[current.y][current.x];
        }
        shortestPath.push_back((Vector2i)startPos);
        reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }

    bool isConnected()
    {
        int visitedc = 0;
        vector<vector<bool>> visited(SIZE, vector<bool>(SIZE, false));
        queue<Vector2i> q;
        q.push(Vector2i(0, 0));
        visited[0][0] = true;

        while (!q.empty())
        {
            Vector2i current = q.front();
            q.pop();
            visitedc++;

            int row = current.y;
            int col = current.x;

            if (row > 0 && !maze[row - 1][col] && !visited[row - 1][col])
            {
                q.push(Vector2i(col, row - 1));
                visited[row - 1][col] = true;
            }
            if (row < SIZE - 1 && !maze[row + 1][col] && !visited[row + 1][col])
            {
                q.push(Vector2i(col, row + 1));
                visited[row + 1][col] = true;
            }
            if (col > 0 && !maze[row][col - 1] && !visited[row][col - 1])
            {
                q.push(Vector2i(col - 1, row));
                visited[row][col - 1] = true;
            }
            if (col < SIZE - 1 && !maze[row][col + 1] && !visited[row][col + 1])
            {
                q.push(Vector2i(col + 1, row));
                visited[row][col + 1] = true;
            }
        }

        int totalNonWalls = SIZE * SIZE - walls;

        if (visitedc == totalNonWalls)
            return true;
        else
            return false;
    }

private:

    vector<vector<bool>> maze;
    RenderWindow& window;
    Texture wall;
    Texture path;
    Texture startPointTex;
    Texture endPointTex;
    Vector2i startPos;
    Vector2i endPos;
};

enum class Direction {Up, Down, Left, Right};
class Robo
{
public:

    Vector2i position;
    Vector2f pix_pos;

    Robo(RenderWindow& window, const Maze& maze)
        :window(window), maze(maze), position(0, 0)
    {

        if (!roboTex.loadFromFile("images/robo_new.png"))
        {
            cout << "Failed to load robo texture." << endl;
            return;
        }
        robo.setTexture(roboTex);
        robo.setTextureRect(IntRect(32*animation,32,32,32));
        robo.setOrigin(16,16);
        robo.setScale(Vector2f(2.45, 2.45));
    }

    void move(vector<Vector2i>& shrtPath)
    {
        Vector2i direction;
        direction.x = shrtPath.front().x - position.x ;
        direction.y =  shrtPath.front().y - position.y;
        pix_pos.x += direction.x * deltatime * 220;
        pix_pos.y += direction.y * deltatime * 220;
        cout<<pix_pos.x<<" "<<pix_pos.y<<" "<<deltatime<<endl;
        if(abs(position.x*CELL_SIZE-pix_pos.x)>=90)
        {
            pix_pos.x = (position.x+direction.x)*CELL_SIZE;
            position.x = position.x + direction.x;
            shrtPath.erase(shrtPath.begin());
        }
        else if(abs(position.y*CELL_SIZE-pix_pos.y)>=90)
        {
            pix_pos.y = (position.y+direction.y)*CELL_SIZE;
            position.y = position.y + direction.y;
            shrtPath.erase(shrtPath.begin());
        }
        if(delay<=0)
        {
            delay=0.1;
            animation++;
            animation%=8;
        }
        else
        {
            delay-=deltatime;
        }

        if(direction.x==1)
        {
            robo.setScale(Vector2f(2.45, 2.45));
            robo.setTextureRect(IntRect(32*animation,96,32,32));
        }
        else if( direction.x==-1)
        {
            robo.setScale(Vector2f(-2.45, 2.45));
            robo.setTextureRect(IntRect(32*animation,96,32,32));
        }
        else if( direction.y==-1)
        {
            robo.setScale(Vector2f(2.45, 2.45));
            robo.setTextureRect(IntRect(32*animation,128,32,32));
        }
        else if( direction.y==1)
        {
            robo.setScale(Vector2f(2.45, 2.45));
            robo.setTextureRect(IntRect(32*animation,64,32,32));
        }

        if(!shrtPath.size())
        {
            //neutral state.
            moving=false;
            animation=0;
            robo.setScale(Vector2f(2.45, 2.45));
            robo.setTextureRect(IntRect(32*animation,32,32,32));
        }
    }
    void draw()
    {
        robo.setPosition(Vector2f((pix_pos.x+44.2), pix_pos.y+39.2));
        window.draw(robo);
    }

    void rePosition(Vector2i rePos)
    {
        position.x = rePos.x / CELL_SIZE;
        position.y = rePos.y / CELL_SIZE;
        pix_pos.x = position.x * CELL_SIZE;
        pix_pos.y = position.y * CELL_SIZE;
    }

private:
    RenderWindow& window;
    const Maze& maze;
    Texture roboTex;
    Sprite robo;
};
int main()
{
    RenderWindow window(VideoMode(SIZE * CELL_SIZE, SIZE * CELL_SIZE), "RoboMaze");

    Maze maze(window);
    Robo robo(window, maze);
    vector<Vector2i> shrtPath;
    Event event;

    interactionwindow1.interactionSetProp(arrayOfInteractions,420, 200,0);
    interactionWindow2.interactionSetProp(arrayOfInteractions,420, 300,1);
    interactionWindow3.interactionSetProp(arrayOfInteractions,420, 400,2);
    seeked.interactionSetProp(arrayOfInteractions2,430,200);

    while (window.isOpen())
    {
        deltatime=game.restart().asSeconds();
        gameclock.restart();
        if(moving)
        {
            robo.move(shrtPath);
            game.restart();
            window.clear();
            maze.draw();
            robo.draw();
            window.display();
        }
        if (!interactionwindow1.finishedInteracting and !interactionWindow2.finishedInteracting)
        {
            interactionwindow1.update(deltatime, window);
        }
        else if (interactionwindow1.finishedInteracting and !interactionWindow2.finishedInteracting)
        {
            interactionWindow2.update(deltatime, window);
        }
        else
        {
            interactionWindow3.update(deltatime, window);
        }

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left&&!moving)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    if (robo.position.x != mousePos.x && robo.position.y != mousePos.y)
                    {
                        maze.handleMouseClick(mousePos);
                    }
                }
                else if (event.mouseButton.button == Mouse::Right&&!moving)
                {
                    Vector2i mousePos = Mouse::getPosition(window);
                    int col = mousePos.x / CELL_SIZE;
                    int row = mousePos.y / CELL_SIZE;
                    if (!maze.isWall(row, col))
                        robo.rePosition(mousePos);
                }
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
            {
                Vector2i End(9, 9);
                if(maze.isConnected()&&!moving)
                {
                    shrtPath = maze.findShortestPath(robo.position, End);
                    shrtPath.erase(shrtPath.begin());
                    moving=true;
                }
                else if(!moving)
                {
                    clicked=true;
                    cout<<"There is UnReachable Path"<<endl;
                }

            }
            if (!interactionwindow1.finishedInteracting)
            {
                if (event.key.code == Keyboard::Space)
                    interactionwindow1.abort();

            }
            if (!interactionWindow2.finishedInteracting)
            {
                if (event.key.code == Keyboard::Space)
                    interactionWindow2.abort();
            }
            if (!interactionWindow3.finishedInteracting)
            {
                if (event.key.code == Keyboard::Space)
                    interactionWindow3.abort();
            }

        }
        if (clicked==true)
        {
            seeked.update(deltatime, window);
            seeked.draw(window);
            if(seeked.finishedInteracting)
            {
                clicked = false;
                seeked.interactionSetProp(arrayOfInteractions2,430,200);
            }
        }
        window.clear();
        maze.draw();
        robo.draw();
        interactionwindow1.draw(window);
        interactionWindow2.draw(window);
        interactionWindow3.draw(window);
        seeked.draw(window);
        window.display();
    }
    return 0;
}
