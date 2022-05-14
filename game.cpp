#include "game.h"

#include <QDebug>

//  Конструктор.
Game::Game()
{
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);

    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);

    //  Загрузка изображений.
    apple_img.load("./textures/apple.png");
    apple_img = apple_img.scaled(30, 30, Qt::KeepAspectRatio);

    head_up_img.load("./textures/head_up.png");
    head_up_img = head_up_img.scaled(30, 30, Qt::KeepAspectRatio);
    head_down_img.load("./textures/head_down.png");
    head_down_img = head_down_img.scaled(30, 30, Qt::KeepAspectRatio);
    head_left_img.load("./textures/head_left.png");
    head_left_img = head_left_img.scaled(30, 30, Qt::KeepAspectRatio);
    head_right_img.load("./textures/head_right.png");
    head_right_img = head_right_img.scaled(30, 30, Qt::KeepAspectRatio);

    body_img.load("./textures/body.png");
    body_img = body_img.scaled(30, 30, Qt::KeepAspectRatio);
    body_vertical_img.load("./textures/body_vertical.png");
    body_vertical_img = body_vertical_img.scaled(30, 30, Qt::KeepAspectRatio);
    body_3_to_6_img.load("./textures/body_3_to_6.png");
    body_3_to_6_img = body_3_to_6_img.scaled(30, 30, Qt::KeepAspectRatio);
    body_6_to_9_img.load("./textures/body_6_to_9.png");
    body_6_to_9_img = body_6_to_9_img.scaled(30, 30, Qt::KeepAspectRatio);
    body_9_to_12_img.load("./textures/body_9_to_12.png");
    body_9_to_12_img = body_9_to_12_img.scaled(30, 30, Qt::KeepAspectRatio);
    body_12_to_3_img.load("./textures/body_12_to_3.png");
    body_12_to_3_img = body_12_to_3_img.scaled(30, 30, Qt::KeepAspectRatio);

    tail_up_img.load("./textures/tail_up.png");
    tail_up_img = tail_up_img.scaled(30, 30, Qt::KeepAspectRatio);
    tail_down_img.load("./textures/tail_down.png");
    tail_down_img = tail_down_img.scaled(30, 30, Qt::KeepAspectRatio);
    tail_left_img.load("./textures/tail_left.png");
    tail_left_img = tail_left_img.scaled(30, 30, Qt::KeepAspectRatio);
    tail_right_img.load("./textures/tail_right.png");
    tail_right_img = tail_right_img.scaled(30, 30, Qt::KeepAspectRatio);

}


//  Таймер (движение игрового процесса).
void Game::timerEvent(QTimerEvent *)
{
    if (m_in_game)
    {
        checkApple();
        move();
        checkField();
    }

    this->repaint();  //  Перерисовать картинку.
}


//  Отрисовка.
void Game::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    doDrawing();
}

//  Главная логика игры, отрисовка.
void Game::doDrawing()
{
    QPainter qp(this);

    if (m_in_game)  //  Пока не проиграли.
    {
        //  Отрисовка яблока.
        qp.drawImage(QPoint(m_apple.x() * DOT_WIDTH, m_apple.y() * DOT_HEIGHT), apple_img);

        //  Отрисовка змейки.
        for (int i = 0; i < m_dots.size(); i++)
        {
            if (i == 0)  //  Отрисовка головы змейки.
            {
                switch (m_dir) {
                case 0:  //  Движется вверх.
                    qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT), head_up_img);
                    break;
                case 1:  //  Движется вправо.
                    qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT), head_right_img);
                    break;
                case 2:  //  Движется вниз.
                    qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT), head_down_img);
                    break;
                case 3:  //  Движется влево.
                    qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT), head_left_img);
                    break;
                }
            }

            else if (i == (m_dots.size() - 1))  //  Отрисовка кончика хвоста змейки.
            {
                //  Хвост тянет вверх.
                if (m_dots[m_dots.size() - 2].y() < m_dots[m_dots.size() - 1].y())
                {
                    qp.drawImage(QPoint(m_dots[m_dots.size() - 1].x() * DOT_WIDTH, m_dots[m_dots.size() - 1].y()
                            * DOT_HEIGHT), tail_down_img);
                }
                //  Хвост тянет вниз.
                else if (m_dots[m_dots.size() - 2].y() > m_dots[m_dots.size() - 1].y())
                {
                    qp.drawImage(QPoint(m_dots[m_dots.size() - 1].x() * DOT_WIDTH, m_dots[m_dots.size() - 1].y()
                            * DOT_HEIGHT), tail_up_img);
                }
                //  Хвост тянет влево.
                else if (m_dots[m_dots.size() - 2].x() < m_dots[m_dots.size() - 1].x())
                {
                    qp.drawImage(QPoint(m_dots[m_dots.size() - 1].x() * DOT_WIDTH, m_dots[m_dots.size() - 1].y()
                            * DOT_HEIGHT), tail_right_img);
                }
                //  Хвост тянет вправо.
                else if (m_dots[m_dots.size() - 2].x() > m_dots[m_dots.size() - 1].x())
                {
                    qp.drawImage(QPoint(m_dots[m_dots.size() - 1].x() * DOT_WIDTH, m_dots[m_dots.size() - 1].y()
                            * DOT_HEIGHT), tail_left_img);
                }
            }

            else //  Отрисовка тела змейки (все кроме головы и кончика хвоста).
            {
                //  Отрисовка прямых частей тела.
                if ((m_dots[i].y() == m_dots[i+1].y())&&(m_dots[i].y() == m_dots[i-1].y()))  //  Горизонтальное положение.
                {
                    qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y()
                            * DOT_HEIGHT), body_img);
                }
                else if ((m_dots[i].x() == m_dots[i+1].x())&&(m_dots[i].x() == m_dots[i-1].x()))  //  Вертикальное положение.
                {
                    qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y()
                            * DOT_HEIGHT), body_vertical_img);
                }

                else
                {
                    //  Отрисовка кривых частей тела.
                    //  12 to 3 pm.
                    if ((m_dots[i].y() == std::min(m_dots[i-1].y(), m_dots[i+1].y()))&&(m_dots[i].x() == std::max(m_dots[i-1].x(), m_dots[i+1].x())))
                    {
                        qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y()
                                * DOT_HEIGHT), body_12_to_3_img);
                    }
                    //  3 to 6 pm.
                    else if ((m_dots[i].y() == std::max(m_dots[i-1].y(), m_dots[i+1].y()))&&(m_dots[i].x() == std::max(m_dots[i-1].x(), m_dots[i+1].x())))
                    {
                        qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y()
                                * DOT_HEIGHT), body_3_to_6_img);
                    }
                    //  6 to 9 pm.
                    else if ((m_dots[i].y() == std::max(m_dots[i-1].y(), m_dots[i+1].y()))&&(m_dots[i].x() == std::min(m_dots[i-1].x(), m_dots[i+1].x())))
                    {
                        qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y()
                                * DOT_HEIGHT), body_6_to_9_img);
                    }
                    //  9 to 12 pm.
                    else if ((m_dots[i].y() == std::min(m_dots[i-1].y(), m_dots[i+1].y()))&&(m_dots[i].x() == std::min(m_dots[i-1].x(), m_dots[i+1].x())))
                    {
                        qp.drawImage(QPoint(m_dots[i].x() * DOT_WIDTH, m_dots[i].y()
                                * DOT_HEIGHT), body_9_to_12_img);
                    }
                }
            }
        }
    }
    else  //  Проигрышь.
    {
        m_in_game = false;
    }
}

//  Спавн яблока.
void Game::localApple()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    m_apple.rx() = qrand() % FIELD_WIDTH;
    m_apple.ry() = qrand() % FIELD_HEIGHT;
}

//  Движение змейки.
void Game::move()
{

    //  Установка начальной позиции змейки.
    for (int i = m_dots.size() - 1; i > 0; i--)
    {
        m_dots[i] = m_dots[i-1];
    }

    //  В зависимости от направления меняем координаты.
    switch (m_dir)
    {
    case 0:    {m_dots[0].ry() -= 1; break;}  //up
    case 1:    {m_dots[0].rx() += 1; break;}  //right
    case 2:    {m_dots[0].ry() += 1; break;}  //down
    case 3:    {m_dots[0].rx() -= 1; break;}  //left
    }
}

//  Обработчик проигрышей.
void Game::checkField()
{
    //  Не съела ли змейка саму себя.
    if (m_dots.size() > 4)
    {
        for (int i = 1; i < m_dots.size(); i++)
        {
            if (m_dots[0] == m_dots[i])
                m_in_game = false;
        }
    }

    //  Не врезалась ли змейка в границы.
    if (m_dots[0].x() >= FIELD_WIDTH)  { m_in_game = false; }
    if (m_dots[0].x() < 0)             { m_in_game = false; }
    if (m_dots[0].y() >= FIELD_HEIGHT) { m_in_game = false; }
    if (m_dots[0].y() < 0)             { m_in_game = false; }

    if (!m_in_game)
    {
        killTimer(m_timer_id);  //  Остановка таймера, в случае проигрыша.
    }
}

//  Проверка, съела ли змейка яблоко.
void Game::checkApple()
{
    if (m_apple == m_dots[0])
    {
        m_dots.push_back(QPoint(0, 0));
        score++;
        localApple();
    }
}

//  Начальная инициализация игры.
void Game::initGame()
{
    m_in_game = true;
    m_dir = 1;
    score = 0;

    m_dots.resize(3);

    for (int i = 0; i < m_dots.size(); i++)
    {
        m_dots[i].rx() = m_dots.size() - i - 1;
        m_dots[i].ry() = 0;
    }

    localApple();

    m_timer_id = startTimer(DELAY);
}
