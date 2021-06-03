            #if 1
//�v�����g�ō�������--------------------------------------------------------------------
#include"libOne.h"
struct DATA {
    //�摜�ǂݍ���
    int playerGuImg;
    int playerCHOkiImg;
    int playerPaImg;
    int pcGuImg;
    int pcCHOkiImg;
    int pcPaImg;
    int heartImg;
    //��̔ԍ������߂Ă���
    int Gu = 0;
    int CHOki = 1;
    int PA = 2;
    //��Ԃ̐؂�ւ�
    int INIT = 0;
    int PLAY = 1;
    int RESULT = 2;
    int state = INIT;
    //�v���C���[�f�[�^
    int   playerHand;
    int   playerImg;
    float playerPx;
    float playerPy;
    float playerAngle;
    float playerR;
    float playerG;
    float playerB;
    int   playerLife;
    //�����f�[�^
    int pcHand;
    int pcImg;
    float pcPx;
    float pcPy;
    float pcAngle;
    float pcR;
    float pcG;
    float pcB;
    int   pcLife;
    //������������
    float resultPx;
    float resultPy;
    float resultSizu;
};

void loadImages(struct DATA* d) {
    d->playerGuImg = loadImage("assets\\playerGu.png");
    d->playerCHOkiImg = loadImage("assets\\playerCHOki.png");
    d->playerPaImg = loadImage("assets\\playerPa.png");
    d->pcGuImg = loadImage("assets\\pcGu.png");
    d->pcCHOkiImg = loadImage("assets\\pcCHOki.png");
    d->pcPaImg = loadImage("assets\\pcPa.png");
    d->heartImg = loadImage("assets\\heart.png");
}


void init(struct DATA* d) {
    //�������O�����l�ݒ�
        //�v���C���[�f�[�^
    d->playerHand = 0;
    d->playerImg = d->playerGuImg;
    d->playerPx = 250;
    d->playerPy = 225;
    d->playerAngle = 0;
    d->playerR = 255;
    d->playerG = 255;
    d->playerB = 255;
    d->playerLife = 3;
    //�����f�[�^
    d->pcHand = d->Gu;
    d->pcImg = d->pcGuImg;
    d->pcPx = 550;
    d->pcPy = 225;
    d->pcAngle = 0;
    d->pcR = 255;
    d->pcG = 255;
    d->pcB = 255;
    d->pcLife = 3;
    //������������
    d->resultPx = 225;
    d->resultPy = 320;
    d->resultSizu = 0;
    //�Q�[�����[�h�ؑ�
    d->state = d->PLAY;
}

void play(struct DATA* d) {
    //A,S,D�����ꂩ�̃L�[�������ꂽ��
    if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
        //�v���C���[�̎�����߂�
        if (isTrigger(KEY_A)) { d->playerHand = d->Gu; }
        else if (isTrigger(KEY_S)) { d->playerHand = d->CHOki; }
        else if (isTrigger(KEY_D)) { d->playerHand = d->PA; }
        //�v���C���[�̉摜��؂�ւ���
        if (d->playerHand == d->Gu) { d->playerImg = d->playerGuImg; }
        else if (d->playerHand == d->CHOki) { d->playerImg = d->playerCHOkiImg; }
        else if (d->playerHand == d->PA) { d->playerImg = d->playerPaImg; }
        //�����̎�����߂�
        d->pcHand = random() % 3;//�����_���Ȑ���%�R�������̎�ɂ���
        //�����̉摜��؂�ւ���
        if (d->pcHand == d->Gu) { d->pcImg = d->pcGuImg; }
        else if (d->pcHand == d->CHOki) { d->pcImg = d->pcCHOkiImg; }
        else if (d->pcHand == d->PA) { d->pcImg = d->pcPaImg; }
        //���������𔻒肵�A�F��ς���
        if (d->playerHand == d->pcHand) {//������
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255; d->pcG = 255; d->pcB = 255;
        }
        else if ((d->playerHand + 1) % 3 == d->pcHand) {//�v���C���[�̏���
            d->playerR = 255; d->playerG = 200; d->playerB = 200;
            d->pcR = 255; d->pcG = 255; d->pcB = 255;
            d->pcLife--;
        }
        else {//�����̏���
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255; d->pcG = 200; d->pcB = 200;
            d->playerLife--;
        }
        //�Q�[���X�e�[�g�؂�ւ�------------------------------------------------------------------------------------
        if (d->playerLife == 0 || d->pcLife == 0) {
            d->state = d->RESULT;
        }
    }
}

void result(struct DATA* d) {
    if (d->state == d->RESULT) {
        if (d->pcLife == 0) {
            //pc����
            d->pcPy += 1.0f;
            d->pcAngle += -0.005f;
        }
        else {
            //�v���C���[����
            d->playerPy += 1.0f;
            d->playerAngle += -0.005f;
        }
        //��������������傫�����Ă���
        if (d->resultSizu < 160) {
            d->resultSizu += 10.0f;
        }

        //�Q�[���X�e�[�g�؂�ւ�
        if (isTrigger(KEY_SPACE)) {
            d->state = d->INIT;
        }
    }
}

void draw(struct DATA* d) {
    //�`��-------------------------------------------------------------------------------------------
    clear(200);
    rectMode(CENTER);
    //�v���C���[�̎�
    imageColor(d->playerR, d->playerG, d->playerB);
    image(d->playerImg, d->playerPx, d->playerPy, d->playerAngle);
    //�����̎�
    imageColor(d->pcR, d->pcG, d->pcB);
    image(d->pcImg, d->pcPx, d->pcPy, d->pcAngle);
    //�v���C���[�n�[�g
    for (int i = 0; i < d->playerLife; i++) {
        imageColor(255, 0, 0);
        image(d->heartImg, d->playerPx - 50 + (50 * i), d->playerPy - 110);
    }
    //�����n�[�g
    for (int o = 0; o < d->pcLife; o++) {
        imageColor(255, 0, 0);
        image(d->heartImg, d->pcPx - 50 + (50 * o), d->pcPy - 110);
    }

    //���������e�L�X�g�`��
    if (d->state == d->RESULT) {
        textSize(d->resultSizu);
        if (d->playerLife > 0) {
            fill(255, 0, 0);
            text("YOU!", d->resultPx, d->resultPy - 80);
            text("WIN!!", d->resultPx, d->resultPy + 50);
        }
        else {
            fill(0, 0, 200);
            text("YOU", d->resultPx - 20, d->resultPy - 80);
            text("lose", d->resultPx + 20, d->resultPy + 50);
        }
    }
}




void gmain() {
    window(800, 450);
    struct DATA d;
    loadImages(&d);
    while (notQuit) {
        if (d.state == d.INIT) { init(&d); }
        else if (d.state == d.PLAY) { play(&d); }
        else if (d.state == d.RESULT) { result(&d); }
        draw(&d);
    }
}
//Youtube�@�ō�������-----------------------------------------------------
/*
#include"libOne.h"

struct HAND {
    int hand;
    int img[3];
    float px, py, angle;
    float R, G, B;
    int life;
};

struct DATA {
    int INIT = 0;
    int PLAY = 1;
    int RESULT = 2;
    int state = INIT;

    int GU = 0;
    int CHOKI = 1;
    int PA = 2;
    struct HAND player;
    struct HAND pc;
    int heartImg;

    float resultSize;
};

void loadImage(struct DATA* d) {
    d->player.img[0] = loadImage("assets\\playerGu.png");
    d->player.img[1] = loadImage("assets\\playerCHOki.png");
    d->player.img[2] = loadImage("assets\\playerPa.png");

    d->pc.img[0] = loadImage("assets\\pcGu.png");
    d->pc.img[1] = loadImage("assets\\pcCHOki.png");
    d->pc.img[2] = loadImage("assets\\pcPa.png");

    d->heartImg = loadImage("assets\\heart.png");
}

void init(struct DATA* d) {
    d->player.hand = d->GU;
    d->player.px = 250;
    d->player.py = 225;
    d->player.angle = 0;

    d->player.R = 255;
    d->player.G = 255;
    d->player.B = 255;

    d->player.life = 3;

    d->pc.hand = d->GU;
    d->pc.px = 800 - 250;
    d->pc.py = 225;
    d->pc.angle = 0;

    d->pc.R = 255;
    d->pc.G = 255;
    d->pc.B = 255;

    d->pc.life = 3;

    d->state = d->PLAY;

    d->resultSize = 0;
}

void play(struct DATA* d) {
    if (!isTrigger(KEY_A) && !isTrigger(KEY_S) && !isTrigger(KEY_D)) {
        return;
    }
    //player �̎�
    if (isTrigger(KEY_A)) { d->player.hand = d->GU; }
    if (isTrigger(KEY_S)) { d->player.hand = d->CHOKI; }
    if (isTrigger(KEY_D)) { d->player.hand = d->PA; }
    //pc�@�̎�
    d->pc.hand = random() % 3;
    //������������
    if (d->player.hand == d->pc.hand) {
        //������
        d->player.R = 255; d->player.G = 255; d->player.B = 255;
        d->pc.R = 255; d->pc.G = 255; d->pc.B = 255;
    }
    else if ((d->player.hand + 1) % 3 == d->pc.hand) {
        //player����
        d->pc.life--;
        d->player.R = 255; d->player.G = 200; d->player.B = 200;
        d->pc.R = 255; d->pc.G = 255; d->pc.B = 255;
    }
    else {
        //pc�̏���
        d->player.life--;
        d->player.R = 255; d->player.G = 255; d->player.B = 255;
        d->pc.R = 255; d->pc.G = 200; d->pc.B = 200;
    }
    if (d->player.life == 0 || d->pc.life == 0) {
        d->state = d->RESULT;
    }
}


void result(struct DATA* d) {
    if (d->player.life == 0) {
        d->player.py += 1;
        d->player.angle += 0.003f;
    }
    else {
        d->pc.py += 1;
        d->pc.angle -= 0.003f;
    }
    if (isTrigger(KEY_SPACE)) {
        d->state = d->INIT;
    }
    if (d->resultSize < 180) {
        d->resultSize += 10;
    }
}

void draw(struct DATA* d) {
    clear(180);
    rectMode(CENTER);

    imageColor(d->player.R, d->player.G, d->player.B);
    image(d->player.img[d->player.hand], d->player.px, d->player.py, d->player.angle);

    imageColor(d->pc.R, d->pc.G, d->pc.B);
    image(d->pc.img[d->pc.hand], d->pc.px, d->pc.py, d->pc.angle);

    for (int i = 0; i < d->player.life; i++) {
        imageColor(255, 0, 0);
        image(d->heartImg, d->player.px + 50 * (i - 1), d->player.py - 110);
    }
    for (int i = 0; i < d->pc.life; i++) {
        imageColor(255, 0, 0);
        image(d->heartImg, d->pc.px + 50 * (i - 1), d->pc.py - 110);
    }
    if (d->state == d->RESULT) {
        textSize(d->resultSize);
        if (d->player.life > 0) {
            fill(255, 0, 0);
            text("����", 225, 320);
        }
        else {
            fill(0, 0, 200);
            text("����", 225, 320);
        }

    }
}

void gmain() {
    window(800, 450);
    struct DATA d;
    //init(&d);
    loadImage(&d);
    while (notQuit) {
        if (d.state == d.INIT) { init(&d); }
        else if (d.state == d.PLAY) { play(&d); }
        if (d.state == d.RESULT) { result(&d); }
        draw(&d);
    }
}
*/
#endif

