#include <iostream>

// Target interface
class MediaPlayer {
public:
    virtual void play(const std::string& fileName) = 0;
    virtual ~MediaPlayer() = default;
};

// Adaptee class
class MediaAdapter {
public:
    void playMedia(const std::string& fileName) {
        std::cout << "Playing " << fileName << " using Media Adapter." << std::endl;
    }
};

// Concrete Target class
class AudioPlayer : public MediaPlayer {
private:
    MediaAdapter mediaAdapter;

public:
    void play(const std::string& fileName) override {
        if (fileName == "mp3") {
            std::cout << "Playing " << fileName << " directly" << std::endl;
        } else {
            mediaAdapter.playMedia(fileName);
        }
    }
};

int main() {
    AudioPlayer audioPlayer;
    audioPlayer.play("mp3");
    audioPlayer.play("wav");

    return 0;
}
