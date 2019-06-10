#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent, bool mode) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*Basics*/

    ui->setupUi(this);
    apples = 0;

    ui->graphicsView->setStyleSheet("background-image :url(:/backgrounds/HomeWallpaper.jpg);background-color:rgba(1,1,1,0.5)");
    //ui->graphicsView->setInteractive(true);
    setCentralWidget(ui->graphicsView);

    B_WIDTH = 600;
    B_HEIGHT = 600;

    RAND_POS = (B_WIDTH/DOT_SIZE)-1;
    qDebug() << " Width " << B_WIDTH << " hight "<< B_HEIGHT;
    qDebug() << ui->graphicsView->size();
    /*Custom width this time*/

    /*Sound*/

    player = new QMediaPlayer;
    effect = new QMediaPlayer;

    player->setMedia(QUrl("qrc:/alerts/rattlesnake4.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
    //player->setPlaybackMode(QMediaPlaylist::Loop);
    player->play();


    /*Scene Setup*/

    //gscene->addRect(0,0,B_WIDTH,B_HEIGHT,pen);


    /*Setup Scenes*/
        /************************************Start Screen Scenes**************************************/
        int middle = B_WIDTH * 0.1;
        int hmiddle = B_HEIGHT * 0.1;
        QPushButton *StartGame = new QPushButton;StartGame->setFixedSize(500,90);
        StartGame->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Start.png);background-repeat: no-repeat;background-position: center; ");
        //QPushButton *WatchGame = new QPushButton;WatchGame->setText("Watch Game");WatchGame->setFixedWidth(250);
        //WatchGame->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Start.png);background-repeat: no-repeat;background-position: center;");
        QPushButton *HighScore = new QPushButton;HighScore->setFixedSize(500,90);
        HighScore->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/HighScore.png);background-repeat: no-repeat;background-position: center;");
        QPushButton *Options = new QPushButton;Options->setFixedSize(500,90);
        Options->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Options.png);background-repeat: no-repeat;background-position: center;");
        QPushButton *Help = new QPushButton;Help->setFixedSize(500,90);
        Help->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Help.png);background-repeat: no-repeat;background-position: center;");
        QPushButton *About = new QPushButton;About->setFixedSize(500,90);
        About->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/About.png);background-repeat: no-repeat;background-position: center;");
        QPushButton *Quit = new QPushButton;Quit->setFixedSize(500,90);
        Quit->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Quit.png);background-repeat: no-repeat;background-position: center;");
        /*Connect Buttons*/
        connect(StartGame,SIGNAL(clicked(bool)),this,SLOT(newGame()));
        connect(HighScore,SIGNAL(clicked(bool)),this,SLOT(viewHighScore()));
        connect(Options,SIGNAL(clicked(bool)),this,SLOT(viewOption()));
        connect(Help,SIGNAL(clicked(bool)),this,SLOT(viewHelp()));
        connect(About,SIGNAL(clicked(bool)),this,SLOT(viewAbout()));
        connect(Quit,SIGNAL(clicked(bool)),this,SLOT(exitOnClos()));
        /*Create and Add*/
        startscreen = new QGraphicsScene(this); //StartScreen scene
        startscreen->addWidget(StartGame)->setPos(middle,hmiddle);
        //startscreen->addWidget(WatchGame)->setPos(middle,50+hmiddle);
        startscreen->addWidget(HighScore)->setPos(middle,100+hmiddle);
        startscreen->addWidget(Options)->setPos(middle,200+hmiddle);
        startscreen->addWidget(Help)->setPos(middle,300+hmiddle);
        startscreen->addWidget(Quit)->setPos(middle,400+hmiddle);
        startscreen->addRect(0,0,B_WIDTH,B_HEIGHT);




        /**************************************Pause Screen*************************************************/
        QPushButton *Resume = new QPushButton;Resume->setText("Resume");Resume->setFixedSize(500,90);
        Resume->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Resume.png);background-repeat: no-repeat;background-position: center; ");
        QPushButton *Restart = new QPushButton;Restart->setText("Restart");Restart->setFixedSize(500,90);
        Restart->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Restart.png);background-repeat: no-repeat;background-position: center; ");
        QPushButton *Home = new QPushButton;Home->setText("Home");Home->setFixedSize(500,90);
        Home->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Home.png);background-repeat: no-repeat;background-position: center; ");
        QPushButton *HighScorePause = new QPushButton;HighScorePause->setFixedSize(500,90);
        HighScorePause->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/HighScore.png);background-repeat: no-repeat;background-position: center;");

        connect(Resume,SIGNAL(clicked(bool)),this,SLOT(Resume()));
        connect(Restart,SIGNAL(clicked(bool)),this,SLOT(newGame()));
        connect(Home,SIGNAL(clicked(bool)),this,SLOT(goHome()));
        connect(HighScorePause,SIGNAL(clicked(bool)),this,SLOT(viewHighScore()));
        PauseScene = new QGraphicsScene(this); //Pause screen scene

        PauseScene->addWidget(Resume)->setPos(middle,100+hmiddle);
        PauseScene->addWidget(Restart)->setPos(middle,200+hmiddle);

        PauseScene->addWidget(HighScorePause)->setPos(middle,300+hmiddle);
        PauseScene->addWidget(Home)->setPos(middle,400+hmiddle);

        /***********************Options Screen**************************************/
        volume_slider = new QSlider;volume_slider->setOrientation(Qt::Horizontal);
        Game_Speed = new QSlider;Game_Speed->setOrientation(Qt::Horizontal);
        Game_Level = new QSlider;Game_Level->setOrientation(Qt::Horizontal);
        set_speed = new QLabel;set_level = new QLabel;

        save = new QPushButton;save->setText("Save");save->setFixedSize(500,90);
        save->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/HighScore.png);background-repeat: no-repeat;background-position: center;");
        connect(save,SIGNAL(clicked(bool)),this,SLOT(savesettings()));
        OptionScene = new QGraphicsScene(this);
        QLabel *temp = new QLabel;
        temp->setText("<strong>Sound</strong>");
        OptionScene->addWidget(temp)->setPos(0,0);
        OptionScene->addWidget(volume_slider)->setPos(0,50);
        temp = new QLabel;


        temp->setText("<strong>Game</strong>");
        OptionScene->addWidget(temp)->setPos(0,100);
        OptionScene->addWidget(Game_Speed)->setPos(25,200);
        OptionScene->addWidget(set_speed)->setPos(260,200);

        temp = new QLabel;
        temp->setText("Game Speed");
        OptionScene->addWidget(temp)->setPos(25,150);
        connect(Game_Speed,SIGNAL(valueChanged(int)),this,SLOT(speedchanged(int)));

        OptionScene->addWidget(Game_Level)->setPos(25,300);
        OptionScene->addWidget(set_level)->setPos(260,300);
        temp = new QLabel;
        temp->setText("Game Level");
        OptionScene->addWidget(temp)->setPos(25,250);
        connect(Game_Level,SIGNAL(valueChanged(int)),this,SLOT(levelchanged(int)));

        QPushButton *close = new QPushButton;close->setFixedSize(500,90);
        close->setStyleSheet("border:none;background-color:rgba(1,1,1,0,0);background-image:url(:/buttons/Back.png);background-repeat: no-repeat;background-position: center;");
        connect(close,SIGNAL(clicked(bool)),this,SLOT(goHome()));
        OptionScene->addWidget(close)->setPos(middle,400);
        OptionScene->addWidget(save)->setPos(middle,600);
        /**********************************Help Screen*****************************************/
        QTextBrowser *help = new QTextBrowser;
        help->setFixedWidth(500);
        help->setStyleSheet("border:1px solid black;border-radius:2px;background-color:rgba(155,155,155,0.5)");
        help->setText("<strong>Navigation<br><br>Keybord Keys: </strong>");
        help->append("\tW -> Move Up");
        help->append("\tS -> Move Down");
        help->append("\tA -> Move Left");
        help->append("\tD -> Move Right");
        helpscene = new QGraphicsScene(this);  //Help Screen scene
        QPushButton *close2 = new QPushButton;
        close2->setText("Close");
        connect(close2,SIGNAL(clicked(bool)),this,SLOT(goHome()));
        helpscene->addWidget(help)->setPos(0,0);
        helpscene->addWidget(close2)->setPos(0,help->height());

        /***********************************HighScore Screen************************************/
        QTextBrowser *scores = new QTextBrowser;//score->setFixedSize(500,500);
        highscorescene = new QGraphicsScene(this);
        highscorescene->addWidget(scores)->setPos(0,0);
        QLabel *label = new QLabel;

        if(username != ""){
            QFile file("data.bin");

            if(file.exists() && file.isReadable()){
                file.open(QFile::ReadWrite);

                scores->setText(file.readAll());
            }else{
                scores->setText("No High Score history");
            }
            file.close();
        }else{
            QFile file("data.bin");
            file.open(QFile::ReadWrite);

            scores->setText(file.readAll());
            if(file.exists() && file.isReadable()){
                file.open(QFile::ReadWrite);

                scores->setText(file.readAll());
            }else{
                scores->setText("You don't have any High Score history");
            }
            file.close();
        }


        /**********************************Game Over Scene**************************************/
        scores->setStyleSheet("background-color:rgba(1,1,1,0.5);color:red");
        gameoverscene = new QGraphicsScene(this);
        QPushButton* RestartGame = new QPushButton;RestartGame->setText("Restart");
        QPushButton* GoHome = new QPushButton;GoHome->setText("Home");
        QPushButton* QuitGame = new QPushButton;QuitGame->setText("Quit");
        edit = new QLineEdit;edit->setFixedWidth(150);
        QPushButton *savegame = new QPushButton;savegame->setText("Save Game");
        connect(RestartGame,SIGNAL(clicked(bool)),this,SLOT(newGame()));
        connect(GoHome,SIGNAL(clicked(bool)),this,SLOT(goHome()));
        connect(QuitGame,SIGNAL(clicked(bool)),this,SLOT(exitOnClos()));
        connect(savegame,SIGNAL(clicked(bool)),this,SLOT(savegameresult()));

        gameoverscene->addWidget(edit)->setPos(middle,50+hmiddle);
        gameoverscene->addWidget(savegame)->setPos(middle+150,50+hmiddle);
        gameoverscene->addWidget(RestartGame)->setPos(middle,100+hmiddle);
        gameoverscene->addWidget(GoHome)->setPos(middle,150+hmiddle);
        gameoverscene->addWidget(QuitGame)->setPos(middle,200+hmiddle);
        gameoverscene->addRect(0,0,B_WIDTH,B_HEIGHT);
        /*About*/

        /*Start Game UI*/
        ui->graphicsView->setScene(startscreen);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::loadImages() {
    /*Insert the images into the vector*/
    for(int i = 0; i < 3;i++){
        if(i == 0){
           gdots.push_back(new QGraphicsPixmapItem(QPixmap(":/iconpack/SnakeHead.png")));
        }else{
           gdots.push_back(new QGraphicsPixmapItem(QPixmap(":/iconpack/SnakeBody.png")));
        }
    }
    dots = 3;
    bonusapple = new QGraphicsPixmapItem(QPixmap(":/images/temp2.jpeg"));
    gapple = new QGraphicsPixmapItem(QPixmap(":/iconpack/Apple.png"));
    gscene->addItem(gapple);

    for (int z = 0; z < dots; z++) {
        x[z] = (B_WIDTH * 0.5) - z * DOT_SIZE;
        y[z] = B_HEIGHT * 0.5;
        gscene->addItem(gdots[z]);
        gdots[z]->setPos(x[z],y[z]);
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "event called";
    // In events where keys are pressed
        int key= event->key();
        /* The MainWindow cannot go the opposite the direction at will
         * The MainWindow must first make a right angled turn
         * And the MainWindow can only go to one direction at a time
         * (Only one direction is true)
         */
        if (((key == Qt::Key_Left) || (key == Qt::Key_A)) && (!rightDirection)) {
            leftDirection = true;
            upDirection = false;
            downDirection = false;
        }

        if (((key == Qt::Key_Right) || (key == Qt::Key_D))  && (!leftDirection)) {
            rightDirection = true;
            upDirection = false;
            downDirection = false;
        }

        if (((key == Qt::Key_Up) || (key == Qt::Key_W)) && (!downDirection)) {
            upDirection = true;
            rightDirection = false;
            leftDirection = false;
        }

        if (((key == Qt::Key_Down) || (key == Qt::Key_S)) && (!upDirection)) {
            downDirection = true;
            rightDirection = false;
            leftDirection = false;
        }

        if (key == Qt::Key_Space) {

            if(timer->isActive()){
                timer->stop();
                ui->graphicsView->setScene(PauseScene);
                //timer2->stop();
                //ui->pushButton->setIcon(QIcon(":/images/play.ico"));
            }
        }
        QWidget::keyPressEvent(event);
}
void MainWindow::initGame() {

    /*Gets the stage from the slider and initialise it to current_stage,this is for
    Free hence the main game should have a stage not within the below for loop*/

    if(current_stage == 0){

    }else if(current_stage == 1){

    }else if(current_stage == 2){
        /*Top Block*/
        int startx = B_WIDTH*0.4;
        int starty = B_WIDTH*0.4;
        qDebug() <<"GAME HEIGHT <<<<<<<<<<<<< x: " << gscene->width() << " y: " << gscene->height();
        for(int i = 0; i < 10;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }
        /*Bottom Block*/
        startx = B_WIDTH*0.4;
        starty = B_WIDTH*0.6;
        for(int i = 10; i < 20;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }
    }else if(current_stage == 3){
        /*Top Block*/
        int startx = B_WIDTH*0.4;
        int starty = B_WIDTH*0.4;
        qDebug() <<"GAME HEIGHT <<<<<<<<<<<<< x: " << gscene->width() << " y: " << gscene->height();
        for(int i = 0; i < 10;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }
        /*Bottom Block*/
        startx = B_WIDTH*0.4;
        starty = B_WIDTH*0.6;
        for(int i = 10; i < 20;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }
    }else if(current_stage == 4){
        /*Horizontal*/
        int x1 = DOT_SIZE;
        int y1 = DOT_SIZE;

        int y2 = DOT_SIZE;
        int x2 = B_WIDTH - 2 * DOT_SIZE;
        //int y2 = ;
        qDebug() << "Adding Top corner";
        for(int i = 0;i < 10; i++){
            //qDebug() << "Adding Horizontal";
            // Top Left : Horizontal
            corner_x[i] = x1;
            corner_y[i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[i],corner_y[i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[i],corner_y[i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
           // qDebug() << "Added x: " << corner_x[i] << " y: " << corner_y[i];
            // Top Left : Vertical
            //qDebug() << "Adding Vertical";
            corner_x[10+i] = DOT_SIZE;
            corner_y[10+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i], corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i], corner_y[10+i],DOT_SIZE,DOT_SIZE);
            y1+=DOT_SIZE;
            //qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
        }
        qDebug() << "X2: " << x2;
        for(int i = 10;i < 20; i++){
            // Top right
            corner_x[10+i] = (x2-10);
            corner_y[10+i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i],corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i],corner_y[10+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
            // Bottom left
            corner_x[20+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[20+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
        }
         x2 = (B_WIDTH - 2 * DOT_SIZE);
         y1 = (B_WIDTH - 2 * DOT_SIZE);
         x1 = DOT_SIZE;
         y2 = (B_WIDTH - 2 * DOT_SIZE);


         for(int i = 20;i < 30; i++){
            // Top right
            corner_x[20+i] = x1;
            corner_y[20+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos( corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
            // Bottom left
            corner_x[30+i] = DOT_SIZE;
            corner_y[30+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            y1-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
        }

        for(int i = 30;i < 40; i++){
            // Top right
            corner_x[30+i] = x2;
            corner_y[30+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
            // Bottom left
            corner_x[40+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[40+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[40+i],corner_y[40+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[40+i],corner_y[40+i],DOT_SIZE,DOT_SIZE);
            y2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[40+i] << " y: " << corner_y[40+i];
        }


    }else if(current_stage == 5){
        /*Horizontal*/
        int x1 = DOT_SIZE;
        int y1 = DOT_SIZE;

        int y2 = DOT_SIZE;
        int x2 = B_WIDTH - 2 * DOT_SIZE;
        //int y2 = ;
        qDebug() << "Adding Top corner";
        for(int i = 0;i < 10; i++){
            //qDebug() << "Adding Horizontal";
            // Top Left : Horizontal
            corner_x[i] = x1;
            corner_y[i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[i],corner_y[i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[i],corner_y[i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
           // qDebug() << "Added x: " << corner_x[i] << " y: " << corner_y[i];
            // Top Left : Vertical
            //qDebug() << "Adding Vertical";
            corner_x[10+i] = DOT_SIZE;
            corner_y[10+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i], corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i], corner_y[10+i],DOT_SIZE,DOT_SIZE);
            y1+=DOT_SIZE;
            //qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
        }
        qDebug() << "X2: " << x2;
        for(int i = 10;i < 20; i++){
            // Top right
            corner_x[10+i] = (x2-10);
            corner_y[10+i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i],corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i],corner_y[10+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
            // Bottom left
            corner_x[20+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[20+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
        }
         x2 = (B_WIDTH - 2 * DOT_SIZE);
         y1 = (B_WIDTH - 2 * DOT_SIZE);
         x1 = DOT_SIZE;
         y2 = (B_WIDTH - 2 * DOT_SIZE);


         for(int i = 20;i < 30; i++){
            // Top right
            corner_x[20+i] = x1;
            corner_y[20+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos( corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
            // Bottom left
            corner_x[30+i] = DOT_SIZE;
            corner_y[30+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            y1-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
        }

        for(int i = 30;i < 40; i++){
            // Top right
            corner_x[30+i] = x2;
            corner_y[30+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
            // Bottom left
            corner_x[40+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[40+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[40+i],corner_y[40+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[40+i],corner_y[40+i],DOT_SIZE,DOT_SIZE);
            y2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[40+i] << " y: " << corner_y[40+i];
        }


    }
    else if(current_stage == 6){
        /*Top Block*/
        int startx = B_WIDTH*0.4;
        int starty = B_WIDTH*0.4;
        qDebug() <<"GAME HEIGHT <<<<<<<<<<<<< x: " << gscene->width() << " y: " << gscene->height();
        for(int i = 0; i < 10;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }
        /*Bottom Block*/
        startx = B_WIDTH*0.4;
        starty = B_WIDTH*0.6;
        for(int i = 10; i < 20;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }

        /*Fill In Corner blocks*/
        /*bottom left Corner blocks*/

        /*Horizontal*/
        int x1 = DOT_SIZE;
        int y1 = DOT_SIZE;

        int y2 = DOT_SIZE;
        int x2 = B_WIDTH - 2 * DOT_SIZE;
        //int y2 = ;
        qDebug() << "Adding Top corner";
        for(int i = 0;i < 10; i++){
            //qDebug() << "Adding Horizontal";
            // Top Left : Horizontal
            corner_x[i] = x1;
            corner_y[i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[i],corner_y[i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[i],corner_y[i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
           // qDebug() << "Added x: " << corner_x[i] << " y: " << corner_y[i];
            // Top Left : Vertical
            //qDebug() << "Adding Vertical";
            corner_x[10+i] = DOT_SIZE;
            corner_y[10+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i], corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i], corner_y[10+i],DOT_SIZE,DOT_SIZE);
            y1+=DOT_SIZE;
            //qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
        }
        qDebug() << "X2: " << x2;
        for(int i = 10;i < 20; i++){
            // Top right
            corner_x[10+i] = (x2-10);
            corner_y[10+i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i],corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i],corner_y[10+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
            // Bottom left
            corner_x[20+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[20+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
        }
         x2 = (B_WIDTH - 2 * DOT_SIZE);
         y1 = (B_WIDTH - 2 * DOT_SIZE);
         x1 = DOT_SIZE;
         y2 = (B_WIDTH - 2 * DOT_SIZE);


         for(int i = 20;i < 30; i++){
            // Top right
            corner_x[20+i] = x1;
            corner_y[20+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos( corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
            // Bottom left
            corner_x[30+i] = DOT_SIZE;
            corner_y[30+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            y1-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
        }

        for(int i = 30;i < 40; i++){
            // Top right
            corner_x[30+i] = x2;
            corner_y[30+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
            // Bottom left
            corner_x[40+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[40+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[40+i],corner_y[40+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[40+i],corner_y[40+i],DOT_SIZE,DOT_SIZE);
            y2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[40+i] << " y: " << corner_y[40+i];
        }


    }
    else if(current_stage == 7){
        /*Top Block*/
        int startx = B_WIDTH*0.4;
        int starty = B_WIDTH*0.4;
        qDebug() <<"GAME HEIGHT <<<<<<<<<<<<< x: " << gscene->width() << " y: " << gscene->height();
        for(int i = 0; i < 10;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }
        /*Bottom Block*/
        startx = B_WIDTH*0.4;
        starty = B_WIDTH*0.6;
        for(int i = 10; i < 20;i++){
            obstacle_x[i] = startx;
            obstacle_y[i] = starty;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(startx,starty);
            gscene->addItem(orange_block);
            gscene->addRect(startx,starty,DOT_SIZE,DOT_SIZE);
            startx+=DOT_SIZE;
        }

        /*Fill In Corner blocks*/
        /*bottom left Corner blocks*/

        /*Horizontal*/
        int x1 = DOT_SIZE;
        int y1 = DOT_SIZE;

        int y2 = DOT_SIZE;
        int x2 = B_WIDTH - 2 * DOT_SIZE;
        //int y2 = ;
        qDebug() << "Adding Top corner";
        for(int i = 0;i < 10; i++){
            //qDebug() << "Adding Horizontal";
            // Top Left : Horizontal
            corner_x[i] = x1;
            corner_y[i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[i],corner_y[i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[i],corner_y[i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
           // qDebug() << "Added x: " << corner_x[i] << " y: " << corner_y[i];
            // Top Left : Vertical
            //qDebug() << "Adding Vertical";
            corner_x[10+i] = DOT_SIZE;
            corner_y[10+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i], corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i], corner_y[10+i],DOT_SIZE,DOT_SIZE);
            y1+=DOT_SIZE;
            //qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
        }
        qDebug() << "X2: " << x2;
        for(int i = 10;i < 20; i++){
            // Top right
            corner_x[10+i] = (x2-10);
            corner_y[10+i] = DOT_SIZE;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[10+i],corner_y[10+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[10+i],corner_y[10+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[10+i] << " y: " << corner_y[10+i];
            // Bottom left
            corner_x[20+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[20+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
        }
         x2 = (B_WIDTH - 2 * DOT_SIZE);
         y1 = (B_WIDTH - 2 * DOT_SIZE);
         x1 = DOT_SIZE;
         y2 = (B_WIDTH - 2 * DOT_SIZE);


         for(int i = 20;i < 30; i++){
            // Top right
            corner_x[20+i] = x1;
            corner_y[20+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos( corner_x[20+i],corner_y[20+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[20+i],corner_y[20+i],DOT_SIZE,DOT_SIZE);
            x1+=DOT_SIZE;
            //y2+=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[20+i] << " y: " << corner_y[20+i];
            // Bottom left
            corner_x[30+i] = DOT_SIZE;
            corner_y[30+i] = y1;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            y1-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
        }

        for(int i = 30;i < 40; i++){
            // Top right
            corner_x[30+i] = x2;
            corner_y[30+i] =(B_WIDTH- 2 * DOT_SIZE);
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[30+i],corner_y[30+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[30+i],corner_y[30+i],DOT_SIZE,DOT_SIZE);
            x2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[30+i] << " y: " << corner_y[30+i];
            // Bottom left
            corner_x[40+i] = (B_WIDTH - 2 * DOT_SIZE);
            corner_y[40+i] = y2;
            orange_block = new QGraphicsPixmapItem(QPixmap(":/images/block_orange.png"));
            orange_block->setPos(corner_x[40+i],corner_y[40+i]);
            gscene->addItem(orange_block);
            gscene->addRect(corner_x[40+i],corner_y[40+i],DOT_SIZE,DOT_SIZE);
            y2-=DOT_SIZE;
            qDebug() << "Added x: " << corner_x[40+i] << " y: " << corner_y[40+i];
        }


    }


    ghost = false;
    locateApple();
    inGame = true;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
    connect(timer,SIGNAL(timeout()),this,SLOT(tick()));
    timer->start(DELAY);
}

void MainWindow::locateApple()
{

    // Place Apple randomly
    qDebug() << "moving apple...";
        QTime time = QTime::currentTime();
        qsrand((uint) time.msec());
        int r = qrand() % RAND_POS;
        apple_x = (r * DOT_SIZE);
        r = qrand() % RAND_POS;
        apple_y = (r * DOT_SIZE);
        for(int i = 0;i < dots;i++){
            // Loop thorough the body of the same and search for the apple
            if(x[i] == apple_x && y[i] == apple_y){
                int r = qrand() % RAND_POS;
                apple_x = (r * DOT_SIZE);
                r = qrand() % RAND_POS;
                apple_y = (r * DOT_SIZE);
            }
        }gapple->setPos(apple_x,apple_y);
        qDebug() << "Setting apple to x: " << apple_x << " y: " << apple_y;
        /*if(bonus){
            QTime time2 = QTime::currentTime();
            qsrand((uint) time2.msec());
            int my = qrand() % RAND_POS;
            bonus_x = (my * DOT_SIZE);
            my = qrand() % RAND_POS;
            bonus_y = (my * DOT_SIZE);
            for(int i = 0;i < dots;i++){
                // Loop thorough the body of the same and search for the apple
                if((x[i] ==  bonus_x && y[i] ==  bonus_y) ||(apple_x ==  bonus_x && apple_y ==  bonus_y)){
                    int my = qrand() % RAND_POS;
                     bonus_x = (my * DOT_SIZE);
                    my = qrand() % RAND_POS;
                     bonus_y = (my * DOT_SIZE);
                }
            }
            bonusapple->setPos( bonus_x, bonus_y);
        }else{
            gapple->setPos(apple_x,apple_y);
        }*/
}

void MainWindow::checkIfAppleEaten()
{
    // Check to see if an apple is eaten

    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        // If the apple has been eaten increase MainWindow size
        qDebug() << "Apple eaten";
        effect->setMedia(QUrl("qrc:/alerts/drip.ogg"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
        effect->play();
        dots++;
        gdots.push_back(new QGraphicsPixmapItem(QPixmap(":/iconpack/SnakeBody.png")));
        //gdots[dots]->setPost(x[(dots)]);
        gscene->addItem(gdots[dots-1]);
        apples++;
        score->setText(QString::number(apples));
        locateApple();
        /*if(apples = 3){
            timer->stop();
        }*/

        //ui->label_2->setText(QString::number(apples));
        // randomly place apple

        /*Check If this level is complete*/
    }

    qDebug() << "========: " << current_stage << " && apples: " << apples;
   /* if(isFree){


    }else{*/
        if(current_stage == 0 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
           gscene->removeItem(gapple);
            //ui->label_2->setText(QString::number(0));
            current_stage += 1;
            //timer->stop(); // reset timer
            loadImages();
            initGame();
        }else if(current_stage == 1 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
             gscene->removeItem(gapple);
            //ui->label_2->setText(QString::number(0));
            current_stage = 2;
            //timer->stop(); // reset timer
            loadImages();
            initGame();
        }else if(current_stage == 2 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
            gscene->removeItem(gapple);
            //ui->label_2->setText(QString::number(0));
            current_stage = 3;
            //timer->stop(); // reset timer
            loadImages();
            initGame();
        }else if(current_stage == 3 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
            gscene->removeItem(gapple);
            //ui->label_2->setText(QString::number(0));
            current_stage = 6;
            //timer->stop(); // reset timer
            loadImages();
            initGame();
        }else if(current_stage == 4 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
            gscene->removeItem(gapple);
            //ui->label_2->setText(QString::number(0));
            current_stage = 5;
            //timer->stop(); // reset timer
            loadImages();
            initGame();
        }else if(current_stage == 5 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
            gscene->removeItem(gapple);
            //ui->label_2->setText(QString::number(0));
            current_stage = 6;
            //timer->stop(); // reset timer
            loadImages();
            initGame();
        }
        else if(current_stage == 6 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
            gscene->removeItem(gapple);
            //ui->label_2->setText(QString::number(0));
            current_stage = 7;
           // timer->stop(); // reset timer
            loadImages();
            initGame();
        }else if(current_stage == 7 && apples == 5){
            // Level one done
            qDebug() << "======================================================";
            for(int i = 0;i < gdots.size();i++){
                gscene->removeItem(gdots[i]); // Clear current Snake
            }
            gscene->removeItem(gapple);
           // ui->label_2->setText(QString::number(0));
            current_stage = 0;
            //timer->stop(); // reset timer
            loadImages();
            initGame();
            }

    }

void MainWindow::checkCollision()
{
    // If inGame is false, this means collision
        /*if(playMode){
            // Collision management for self playing game
        }else{*/
    if(current_stage == 0){
        /*Allow through move*/
        if (y[0] >= B_HEIGHT) {
            y[0] = 0;
        }
        if (y[0] < 0) {
            y[0] = B_HEIGHT-DOT_SIZE;
        }
        if (x[0] > B_WIDTH) {
            x[0] = 0;
        }
        if (x[0] < 0) {
            x[0] = B_WIDTH;
        }
        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
    }
    }// Collision management for game play
    if(current_stage == 1){
       /* if(x[0] >= B_WIDTH){
            qDebug() << "Colided...";
            int temp = B_WIDTH-DOT_SIZE;
            for(int z = 0; z < dots;z++){
                x[z] = temp - DOT_SIZE;temp -= DOT_SIZE;
                qDebug() << "Temp =" << temp;
                qDebug() << "Returning z " << z << " to x: " << x[z] << " y: " << y[z];
                timer->stop();
            }
        }*/
        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
        }
        if (y[0] >= B_HEIGHT) {
            // If colided(higher than) with the top
            inGame = false;
            effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
            effect->play();
        }
        if (y[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }
        if (x[0] >= B_WIDTH) {
            // If colided(past over) with the sides
            inGame = false;
          //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
           // effect->play();
        }
        if (x[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }
    }
    if(current_stage == 2){
        /*Allow through move*/
        if (y[0] >= B_HEIGHT) {
            y[0] = 0;
        }
        if (y[0] < 0) {
            y[0] = B_HEIGHT-DOT_SIZE;
        }
        if (x[0] > B_WIDTH) {
            x[0] = 0;
        }
        if (x[0] < 0) {
            x[0] = B_WIDTH;
        }
        /*Added Some obstacles to the game*/
        qDebug() << "------------------------------------------------------------------------";
        qDebug() << "\n";
        for (int i = 0; i < 20;i++) {
                qDebug() << "Checking Stage 2 y " << y[0] << " to obstacle_y " << obstacle_y[i];
                qDebug() << "Checking Stage 2 x " << x[0] << " to obstacle_x " << obstacle_x[i];
                if (y[0] == obstacle_y[i] && x[0] == obstacle_x[i]) {
                    qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                    // If colided(higher than) with the top
                    inGame = false;
                    effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                }
        }
        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
         }
        qDebug() << "\n";
    }if(current_stage==3 ){

        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
        }
        if (y[0] >= B_HEIGHT) {
            // If colided(higher than) with the top
            inGame = false;
            effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
            effect->play();
        }
        if (y[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }
        if (x[0] >= B_WIDTH) {
            // If colided(past over) with the sides
            inGame = false;
          //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
           // effect->play();
        }
        if (x[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }
                for (int i = 0; i < 20;i++) {
                        qDebug() << "Checking Stage 2 y " << y[0] << " to obstacle_y " << obstacle_y[i];
                        qDebug() << "Checking Stage 2 x " << x[0] << " to obstacle_x " << obstacle_x[i];
                        if (y[0] == obstacle_y[i] && x[0] == obstacle_x[i]) {
                            qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                            // If colided(higher than) with the top
                            inGame = false;
                            effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                            effect->play();
                        }
                }
    }if(current_stage == 4){
        /*Allow through move*/
        if (y[0] >= B_HEIGHT) {
            y[0] = 0;
        }
        if (y[0] < 0) {
            y[0] = B_HEIGHT-DOT_SIZE;
        }
        if (x[0] > B_WIDTH) {
            x[0] = 0;
        }
        if (x[0] < 0) {
            x[0] = B_WIDTH;
        }

        for (int i = 0; i < 80;i++) {
                qDebug() << "Checking Stage 2 y " << y[0] << " to corner_y " << corner_y[i];
                qDebug() << "Checking Stage 2 x " << x[0] << " to corner_x " << corner_x[i];
                if (y[0] == corner_y[i] && x[0] == corner_x[i]) {
                    qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                    // If colided(higher than) with the top
                    inGame = false;
                    effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                }
        }
        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
        }
        qDebug() << "\n";
    }if(current_stage == 5){
        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
        }
        if (y[0] >= B_HEIGHT) {
            // If colided(higher than) with the top
            inGame = false;
            effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
            effect->play();
        }
        if (y[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }
        if (x[0] >= B_WIDTH) {
            // If colided(past over) with the sides
            inGame = false;
          //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
           // effect->play();
        }
        if (x[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }

        for (int i = 0; i < 80;i++) {
                qDebug() << "Checking Stage 2 y " << y[0] << " to corner_y " << corner_y[i];
                qDebug() << "Checking Stage 2 x " << x[0] << " to corner_x " << corner_x[i];
                if (y[0] == corner_y[i] && x[0] == corner_x[i]) {
                    qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                    // If colided(higher than) with the top
                    inGame = false;
                    effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                }
        }
        qDebug() << "\n";
    }
    if(current_stage == 6){
        /*Allow through move*/
        if (y[0] >= B_HEIGHT) {
            y[0] = 0;
        }
        if (y[0] < 0) {
            y[0] = B_HEIGHT-DOT_SIZE;
        }
        if (x[0] > B_WIDTH) {
            x[0] = 0;
        }
        if (x[0] < 0) {
            x[0] = B_WIDTH;
        }
        /*Added Some obstacles to the game*/
        qDebug() << "------------------------------------------------------------------------";
        qDebug() << "\n";
        for (int i = 0; i < 20;i++) {
                qDebug() << "Checking Stage 2 y " << y[0] << " to obstacle_y " << obstacle_y[i];
                qDebug() << "Checking Stage 2 x " << x[0] << " to obstacle_x " << obstacle_x[i];
                if (y[0] == obstacle_y[i] && x[0] == obstacle_x[i]) {
                    qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                    // If colided(higher than) with the top
                    inGame = false;
                    effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                }
        }
        for (int i = 0; i < 80;i++) {
                qDebug() << "Checking Stage 2 y " << y[0] << " to corner_y " << corner_y[i];
                qDebug() << "Checking Stage 2 x " << x[0] << " to corner_x " << corner_x[i];
                if (y[0] == corner_y[i] && x[0] == corner_x[i]) {
                    qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                    // If colided(higher than) with the top
                    inGame = false;
                    effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                }
        }
        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
        }
        qDebug() << "\n";
    }
    if(current_stage == 7){
        if (y[0] >= B_HEIGHT) {
            // If colided(higher than) with the top
            inGame = false;
            effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
            effect->play();
        }
        if (y[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }
        if (x[0] >= B_WIDTH) {
            // If colided(past over) with the sides
            inGame = false;
          //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
           // effect->play();
        }
        if (x[0] < 0) {
            inGame = false;
            //  effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
             // effect->play();
        }
        /*Added Some obstacles to the game*/
        qDebug() << "------------------------------------------------------------------------";
        qDebug() << "\n";
        for (int i = 0; i < 20;i++) {
                qDebug() << "Checking Stage 2 y " << y[0] << " to obstacle_y " << obstacle_y[i];
                qDebug() << "Checking Stage 2 x " << x[0] << " to obstacle_x " << obstacle_x[i];
                if (y[0] == obstacle_y[i] && x[0] == obstacle_x[i]) {
                    qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                    // If colided(higher than) with the top
                    inGame = false;
                    effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                }
        }
        for (int i = 0; i < 80;i++) {
                qDebug() << "Checking Stage 2 y " << y[0] << " to corner_y " << corner_y[i];
                qDebug() << "Checking Stage 2 x " << x[0] << " to corner_x " << corner_x[i];
                if (y[0] == corner_y[i] && x[0] == corner_x[i]) {
                    qDebug() << "||||||||||||||Colided with obstacle|||||||||||||||||| ";
                    // If colided(higher than) with the top
                    inGame = false;
                    effect->setMedia(QUrl("qrc:/alerts/sonar.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                }
        }
        if(ghost){

        }else{
        for (int z = dots; z > 0; z--) {
                if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
                    effect->setMedia(QUrl("qrc:/alerts/yellau.wav"));//QUrl::fromLocalFile("":/alerts/sonar.ogg"")
                    effect->play();
                    inGame = false;
                }
            }
        }
        qDebug() << "\n";
    }
    if(!inGame) {
        timer->stop();
        //timer2->stop();
        //QThread::sleep(2000);
        int middle = B_WIDTH * 0.25;
        int hmiddle = B_HEIGHT * 0.25;
        QLabel *temp = new QLabel;temp;temp->setText(" : "+QString::number(apples));
        QGraphicsPixmapItem* disp =new QGraphicsPixmapItem(QPixmap(":/iconpack/Apple.png"));
        disp->setPos(middle,hmiddle);
        gameoverscene->addItem(disp);
        gapple->setPos(middle,hmiddle);
        gameoverscene->addWidget(temp)->setPos(middle+50,hmiddle);

        temp = new QLabel;temp;temp->setText("Time : "+QString::number(apples));
        gameoverscene->addWidget(temp)->setPos(middle+100,hmiddle);
        temp = new QLabel;temp->setText(QString::number(sc));
        gameoverscene->addWidget(temp)->setPos(middle+150,hmiddle);
        ui->graphicsView->setScene(gameoverscene);


    }else{
                    // Move the MainWindow
    }
}

void MainWindow::move()
{
    // The MainWindow can only move to one direction a time

    // Icon overlap crashes code
        qDebug() << "Moving";
        for (int z = dots; z > 0; z--) {
            x[z] = x[(z - 1)];
            y[z] = y[(z - 1)];
        }

        if (leftDirection) {
            x[0] -= DOT_SIZE;
            qDebug() << "going " << "left";
            getMoveDirection("left");
        }

        if (rightDirection) {
                x[0] += DOT_SIZE;
                qDebug() << "going " << "right";
                getMoveDirection("right");
        }

        if (upDirection) {
            y[0] -= DOT_SIZE;
            qDebug() << "going " << "up";
            getMoveDirection("up");
        }
        if (downDirection) {
            y[0] += DOT_SIZE;
            qDebug() << "going " << "down";
            getMoveDirection("down");
        }
        checkIfAppleEaten();
        checkCollision();
        if(inGame){
            for(int z = 0; z < dots;z++){
                qDebug() << "comparing " << x[z] << " with " << B_WIDTH;
                qDebug() << "Setting z " << z << " to x: " << x[z] << " y: " << y[z];
                gdots[z]->setPos(x[z],y[z]);
                /*if(!(x[z] >= B_WIDTH)){
                    qDebug() << "Setting z " << z << " to x: " << x[z] << " y: " << y[z];
                    gdots[z]->setPos(x[z],y[z]);
                }else{
                    for (int z = dots; z > 0; z--) {
                        x[z] = x[(z - 1)];
                        y[z] = y[(z - 1)];
                    }
                    //timer->stop();
                    //break;
                }*/
            }
        }


}

/***SLOTS***/
void MainWindow::tick()
{
    qDebug() << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^";
    sc+DELAY;
    if(sc>=60){
        mn++;
        sc=0;
    }
    if(mn>=60){
        hr++;
        mn=0;
    }
    if(hr>=24)
        hr=0;
    std::stringstream ss;
    if(hr<10)
          ss<<0<<hr<<":";
    else
        ss<<hr<<":";
    if(mn<10)
        ss<<0<<mn<<":";
    else
        ss<<mn<<":";
    if(sc<10)
        ss<<0<<sc;
    else
        ss<<sc;
    QString qs(ss.str().c_str());
    ptimer->setText(QString::number(sc));
}

void MainWindow::pause()
{
    if(timer->isActive()){
        timer->stop();
        timer2->stop();
        ui->pushButton->setIcon(QIcon(":/images/play.ico"));
    }else{
        timer->start();
        timer2->start();
        ui->pushButton->setIcon(QIcon(":/images/pause.ico"));
    }
}

void MainWindow::timerEvent()
{
    //Q_UNUSED(e);
        //connect(timer,SIGNAL(timeout()),this,SLOT(update()));
        //if (inGame) {
            // If the MainWindow hasnt died yet
            qDebug() << "time moving";
            //if(playMode){
                // If the game was told to self play
              //  checkApple();
              //  getAutoDirection();
               // checkCollision();
                //move();
            //}else{
                checkIfAppleEaten();       // Place apple randomly
                //getAutoDirection();
                checkCollision();   // Check if the MainWindow has collided to stop the game
                move();
           // }
       // }
        // Puts the MainWindow on the screen or display game over text
                //repaint();
}
/**************/
void MainWindow::getAutoDirection(){
    if (x[0] < apple_x) {
        // Apple on the right of the MainWindow
        getMoveDirection("right");
    }
    if (x[0] > apple_x) {
        // Apple on the left of the MainWindow
        getMoveDirection("left");
    }
    if (y[0] < apple_y) {
        // Apple is below
        getMoveDirection("down");
    }
    if (y[0] > apple_y){
        //Apple is up
       getMoveDirection("up");
    }
}
void MainWindow::getMoveDirection(QString dir){
    if ((dir == "left") && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((dir == "right") && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((dir == "up") && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((dir == "down") && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(!(gscene->isActive())){
        ui->graphicsView->setScene(gscene);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    //SetScene("StartGame");
}

void MainWindow::on_pushButton_4_clicked()
{
    if(timer->isActive()){
        timer->stop();
    }
    if(timer2->isActive()){
        timer2->stop();
    }
    ui->graphicsView->setScene(startscreen);
}


bool MainWindow::SetScene()
{
    ui->graphicsView->setScene(gscene);
}

bool MainWindow::newGame()
{

    /*Reset Scene*/
    apples = 0;
    dots = 0;
    gdots.clear();
    //gscene->clear();
    // Reset directions
    rightDirection = true;
    upDirection = false;
    downDirection = false;

    /*Create new Game play Scene*/
    QLabel *temp = new QLabel;
    gscene = new QGraphicsScene(this);     //game scene
    gscene->addRect(0,0,B_WIDTH+DOT_SIZE,B_HEIGHT);
    temp = new QLabel;
    temp->setText("Score: ");
    gscene->addWidget(temp)->setPos(0,-50);
    score = new QLabel;
    gscene->addWidget(score)->setPos(temp->width()+5,-50);
    //gscene->addWidget(score);
    temp = new QLabel;temp->setText("Time: ");
    gscene->addWidget(temp)->setPos(75,-50);
    ptimer = new QLabel;
    gscene->addWidget(ptimer)->setPos(125,-50);

    loadImages();

    ui->graphicsView->setStyleSheet("background-image :url(:/iconpack/BackGround.png);background-color:rgba(1,1,1,0.5)");
    //loadImages();
    ui->graphicsView->setScene(gscene);
    initGame();
}

bool MainWindow::watchGame()
{
    loadImages();
    initGame();
}

bool MainWindow::viewHighScore()
{
    ui->graphicsView->setScene(highscorescene);
}

bool MainWindow::goHome()
{
     ui->graphicsView->setStyleSheet("background-image :url(:/backgrounds/HomeWallpaper.jpg);background-color:rgba(1,1,1,0.5)");
    ui->graphicsView->setScene(startscreen);
}
bool MainWindow::viewHelp()
{
    ui->graphicsView->setScene(helpscene);
}

bool MainWindow::viewAbout()
{
    ui->graphicsView->setScene(aboutscene);
}

bool MainWindow::Resume()
{
    ui->graphicsView->setScene(gscene);
    timer->start();
}
bool MainWindow::exitOnClos(){
    QMessageBox *confirm = new QMessageBox;
    confirm->setWindowTitle("Confirm Quit");
    confirm->setText("Are you sure you want to exit the game?");

    confirm->setStandardButtons(QMessageBox::Yes);
    confirm->addButton(QMessageBox::No);
    confirm->setDefaultButton(QMessageBox::No);

    ;
    if(confirm->exec() == QMessageBox::Yes){
        this->close();
    }else{

    }
}

bool MainWindow::viewOption()
{
    ui->graphicsView->setScene(OptionScene);
}

bool MainWindow::savesettings()
{
    DELAY = Game_Speed->value()/11;
    mystage =Game_Level->value()/11;
}

void MainWindow::speedchanged(int speed)
{
    set_speed->setText(QString::number(speed));
}

void MainWindow::levelchanged(int level)
{
    set_level->setText(QString::number(level));
}

bool MainWindow::savegameresult()
{
    if(username != ""){
        QFile file(username+".bin");
        file.open(QFile::WriteOnly);
        //QTextStream stream();
        //file.write(username+"-"+QString::number(apples));
        file.close();
    }else{
        QFile file("data.bin");
        file.open(QFile::WriteOnly);

        if(edit->text() == ""){
            QMessageBox *confirm = new QMessageBox;
            confirm->setWindowTitle("Confirm Quit");
            confirm->setText("Please enter your name");
            edit->setStyleSheet("border:1px solid red;");
            confirm->setStandardButtons(QMessageBox::Ok);
            confirm->setDefaultButton(QMessageBox::Ok);
            confirm->exec();
        }else{
            QTextStream stream(&file);
            stream << edit->text() + "-" + score->text();
        }
        file.close();
    }
}

bool MainWindow::savegame()
{

}
