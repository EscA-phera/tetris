#include <SFML/Graphics.hpp>
#include <ctime>

int field[20][10] = { 0 };

struct Point {
    int x, y;
} a[4], b[4];

int figure[7][4] = {
        1, 3, 5, 7,
        2, 4, 5, 7,
        3, 5, 4, 6,
        3, 5, 4, 7,
        2, 3, 5, 7,
        3, 5, 7, 6,
        2, 3, 4, 5,
};

bool check()
{
    for (int i = 0; i < 4; i++)
    {
        if (a[i].x < 0 || a[i].x >= 10 || a[i].y >= 20) return 0;
        else if (field[a[i].y][a[i].x]) return 0;
    }

    return 1;
};

int main() {
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
    sf::Clock clock;

    sf::Texture texture, background, frame;
    texture.loadFromFile("../images/tiles.png");
    background.loadFromFile("../images/background.png");
    frame.loadFromFile("../images/frame.png");

    sf::Sprite sprite(texture), SpriteBackground(background), SpriteFrame(frame);
    sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

    int dx = 0;
    bool rotate = false;
    int colorNumber = 1;

    float timer = 0;
    float delay = 0.3;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        timer += time;

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) window.close();
            if (e.type == sf::Event::KeyPressed)
                if (e.key.code == sf::Keyboard::Up) rotate = true;
                else if (e.key.code == sf::Keyboard::Left) dx = -1;
                else if (e.key.code == sf::Keyboard::Right) dx = 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) delay = 0.05;

        for (int i = 0; i < 4; i++)
        {
            b[i] = a[i];
            a[i].x += dx;
        }

        if (!check())
        {
            for (int i = 0; i < 4; i++) a[i] = b[i];
        }

        if (rotate)
        {
            Point point = a[1];
            for (int i = 0; i < 4; i++)
            {
                int x = a[i].y - point.y;
                int y = a[i].x - point.x;

                a[i].x = point.x - x;
                a[i].y = point.y + y;
            }

            if (!check())
            {
                for (int i = 0; i < 4; i++)
                {
                    a[i] = b[i];
                }
            }
        }

        if (timer > delay)
        {
            for (int i = 0; i < 4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }

            if (!check())
            {
                for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNumber;

                colorNumber = 1 + rand() % 7;
                int n = rand() % 7;

                for (int i = 0; i < 4; i ++)
                {
                    a[i].x = figure[n][i] % 2;
                    a[i].y = figure[n][i] / 2;
                }
            }

            timer = 0;
        }

        int keyboardLine = 19;
        for (int i = keyboardLine; i > 0; i--)
        {
            int count = 0;

            for (int j = 0; j < 10; j++)
            {
                if (field[i][j]) count++;
                field[keyboardLine][j] = field[i][j];
            }

            if (count < 10) keyboardLine--;
        }

        dx = 0;
        rotate = false;
        delay = 0.3;

        window.clear(sf::Color::White);
        window.draw(SpriteBackground);

        for (int i = 0; i < 20; i ++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (field[i][j] == 0) continue;
                sprite.setTextureRect(sf::IntRect(field[i][j]*18, 0, 18, 18));
                sprite.setPosition(j*18, i*18);
                sprite.move(28, 31);
                window.draw(sprite);
            }
        }

        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(sf::IntRect(colorNumber*18, 0, 18, 18));
            sprite.setPosition(a[i].x*18, a[i].y*18);
            sprite.move(28, 31);
            window.draw(sprite);
        }

        window.draw(SpriteFrame);
        window.display();
    }

    return 0;
}
