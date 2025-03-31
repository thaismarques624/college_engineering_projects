#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;

const int FOOD_SIZE = 20;
const int GAME_DURATION = 60; // 60 segundos de duração do jogo
const int SCREEN_WIDTH = 640; // Largura da tela
const int SCREEN_HEIGHT = 480; // Altura da tela

int score = 0;
bool gameOver = false;
bool gameRunning = true;
bool gameInitialized = false;

struct Food {
    Point position;
    Food() {
        // Gere uma posição aleatória respeitando os limites da tela
        position.x = rand() % (SCREEN_WIDTH - FOOD_SIZE);
        position.y = rand() % (SCREEN_HEIGHT - FOOD_SIZE);
    }
};

vector<Food> foods;
Rect faceRect;
CascadeClassifier faceCascade;
time_t startTime;

void generateFood() {
    foods.clear();
    foods.push_back(Food());
}

void drawFoods(Mat& frame) {
    for (const Food& food : foods) {
        Point pt1 = food.position;
        Point pt2(food.position.x + FOOD_SIZE, food.position.y + FOOD_SIZE);
        rectangle(frame, pt1, pt2, Scalar(0, 0, 255), -1);
    }
}

void updateGame(Mat& frame) {
    if (!gameInitialized) {
        generateFood();
        startTime = time(NULL);
        gameInitialized = true;
        score = 0; // Reseta a pontuação para zero
    }

    if (time(NULL) - startTime >= GAME_DURATION) {
        gameOver = true;
    }

    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    equalizeHist(gray, gray);
    vector<Rect> faces;
    faceCascade.detectMultiScale(gray, faces, 1.3, 5);

    if (!faces.empty()) {
        faceRect = faces[0]; // Use the first detected face
    } else {
        faceRect = Rect();
    }

    drawFoods(frame);

    if (!foods.empty()) {
        for (const Food& food : foods) {
            if (faceRect.area() > 0 && faceRect.x < food.position.x + FOOD_SIZE &&
                faceRect.x + faceRect.width > food.position.x && faceRect.y < food.position.y + FOOD_SIZE &&
                faceRect.y + faceRect.height > food.position.y) {
                score++;
                generateFood();
            }
        }
    }

    if (gameOver) {
        putText(frame, "Fim de Jogo! Sua Pontuacao: " + to_string(score), Point(10, 90), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        putText(frame, "'R' para reiniciar | 'Esc' para sair", Point(10, 120), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
      
    } else {
        putText(frame, "Pontos: " + to_string(score), Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
        int remainingTime = GAME_DURATION - (time(NULL) - startTime);
        putText(frame, "Tempo restante: " + to_string(remainingTime) + "s", Point(10, 60), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
    }
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Erro ao abrir a webcam!" << endl;
        return -1;
    }

    Mat frame;

    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        cerr << "Erro ao carregar o classificador em cascata de rostos!" << endl;
        return -1;
    }

    srand(static_cast<unsigned>(time(0)));

    namedWindow("Jogo da Cobrinha", WINDOW_AUTOSIZE);

    while (gameRunning) {
        cap >> frame;
        if (frame.empty())
            break;
        updateGame(frame);
        rectangle(frame, faceRect, Scalar(0, 255, 0), 2); // Desenha a área do rosto
        imshow("Jogo da Cobrinha", frame);

        char key = waitKey(50);
        if (key == 27) { // Tecla Esc para sair
            // Grava a pontuação atual no arquivo antes de sair
            ofstream highScoreFile("highscore.txt", ios::app);
            if (highScoreFile.is_open()) {
                highScoreFile << score << endl;
                highScoreFile.close();
            }
            gameRunning = false;
        } else if (key == 'r' && gameOver) {
            // Grava a pontuação atual no arquivo antes de reiniciar o jogo
            ofstream highScoreFile("highscore.txt", ios::app);
            if (highScoreFile.is_open()) {
                highScoreFile << score << endl;
                highScoreFile.close();
            }

            gameOver = false;
            gameInitialized = false;
            score = 0; // Reseta a pontuação
            startTime = time(NULL); // Reseta o cronômetro
        }
    }

    cap.release();
    destroyAllWindows();

    return 0;
}


