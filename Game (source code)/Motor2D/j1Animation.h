#ifndef __j1Animation_H__
#define __j1Animation_H__

#include "Brofiler.h"
#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class j1Animation {
public:
	bool loop = true;
	bool pingpong = false;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];

private:
	float current_frame = 0.0f;
	int last_frame = 0;
	int loops = 0;

	enum pingpong {
		forward,
		backward
	};

	enum pingpong direction = forward;

public:
	j1Animation() {}

	j1Animation(const j1Animation& anim) : loop(anim.loop), speed(anim.speed), last_frame(anim.last_frame) {
		SDL_memcpy(&frames, anim.frames, sizeof(frames));
	}

	void PushBack(const SDL_Rect& rect) {
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame() {
		switch (direction) {
		case pingpong::forward: {
			current_frame += speed;

			if (current_frame >= last_frame) {
				current_frame = (loop || pingpong) ? 0.0f : last_frame - 1;
				direction = pingpong ? pingpong::backward : pingpong::forward;
				loops++;
			}
		}
		break;
		case pingpong::backward: {
			current_frame -= speed;

			if (current_frame <= 0.0f) {
				current_frame = 0.0f;
				direction = pingpong::forward;
				loops++;
			}
		}
		break;
		}

		return frames[(int)current_frame];
	}

	bool Finished() const {
		return loops > 0;
	}

	void Reset() {
		current_frame = 0.0f;
	}
};

#endif#