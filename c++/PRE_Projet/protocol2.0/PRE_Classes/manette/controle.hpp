#ifndef CONTROLE_HPP
#define CONTROLE_HPP

#include <linux/joystick.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "../moteur/moteur.hpp"

struct axis_state {
    short x, y;
};

int read_event(int fd, struct js_event *event);

size_t get_axis_count(int fd);

size_t get_button_count(int fd);

size_t get_axis_state(struct js_event *event, struct axis_state axes[3]);

#endif