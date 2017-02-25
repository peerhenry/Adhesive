#pragma once
#include <map>
#include <string>
#include <utility>
#include "GlfwCallbackProvider.h"
#include "pegcore/Command.h"
using std::map;
using std::string;
using std::pair;
using pegcore::command;
using pegcore::InputCallback;

namespace peg_glfw{
 
  struct GlfwControls {
    static map<string, int> get() {
      map<string, int> m;
      m["a"] = GLFW_KEY_A;
      m["b"] = GLFW_KEY_B;
      m["c"] = GLFW_KEY_C;
      m["d"] = GLFW_KEY_D;
      m["e"] = GLFW_KEY_E;
      m["f"] = GLFW_KEY_F;
      m["g"] = GLFW_KEY_G;
      m["h"] = GLFW_KEY_H;
      m["i"] = GLFW_KEY_I;
      m["j"] = GLFW_KEY_J;
      m["k"] = GLFW_KEY_K;
      m["l"] = GLFW_KEY_L;
      m["m"] = GLFW_KEY_M;
      m["n"] = GLFW_KEY_N;
      m["o"] = GLFW_KEY_O;
      m["p"] = GLFW_KEY_P;
      m["q"] = GLFW_KEY_Q;
      m["r"] = GLFW_KEY_R;
      m["s"] = GLFW_KEY_S;
      m["t"] = GLFW_KEY_T;
      m["u"] = GLFW_KEY_U;
      m["v"] = GLFW_KEY_V;
      m["w"] = GLFW_KEY_W;
      m["x"] = GLFW_KEY_X;
      m["y"] = GLFW_KEY_Y;
      m["z"] = GLFW_KEY_Z;

      m["1"] = GLFW_KEY_1;
      m["2"] = GLFW_KEY_2;
      m["3"] = GLFW_KEY_3;
      m["4"] = GLFW_KEY_4;
      m["5"] = GLFW_KEY_5;
      m["6"] = GLFW_KEY_6;
      m["7"] = GLFW_KEY_7;
      m["8"] = GLFW_KEY_8;
      m["9"] = GLFW_KEY_9;
      m["0"] = GLFW_KEY_0;

      m["f1"] = GLFW_KEY_F1;
      m["f2"] = GLFW_KEY_F2;
      m["f3"] = GLFW_KEY_F3;
      m["f4"] = GLFW_KEY_F4;
      m["f5"] = GLFW_KEY_F5;
      m["f6"] = GLFW_KEY_F6;
      m["f7"] = GLFW_KEY_F7;
      m["f8"] = GLFW_KEY_F8;
      m["f9"] = GLFW_KEY_F9;
      m["f10"] = GLFW_KEY_F10;
      m["f11"] = GLFW_KEY_F11;
      m["f12"] = GLFW_KEY_F12;

      m["print-screen"] = GLFW_KEY_PRINT_SCREEN;
      m["scroll-lock"] = GLFW_KEY_SCROLL_LOCK;
      m["pause"] = GLFW_KEY_PAUSE;

      m["insert"] = GLFW_KEY_INSERT;
      m["home"] = GLFW_KEY_HOME;
      m["page-up"] = GLFW_KEY_PAGE_UP;
      m["delete"] = GLFW_KEY_DELETE;
      m["end"] = GLFW_KEY_END;
      m["page-down"] = GLFW_KEY_PAGE_DOWN;

      m["`"] = GLFW_KEY_GRAVE_ACCENT;
      m["-"] = GLFW_KEY_MINUS;
      m["="] = GLFW_KEY_EQUAL;
      m["escape"] = GLFW_KEY_ESCAPE;

      m["tab"] = GLFW_KEY_TAB;
      m["["] = GLFW_KEY_LEFT_BRACKET;
      m["]"] = GLFW_KEY_RIGHT_BRACKET;
      m["\\"] = GLFW_KEY_BACKSLASH;

      m["capslock"] = GLFW_KEY_CAPS_LOCK;
      m[";"] = GLFW_KEY_SEMICOLON;
      m["'"] = GLFW_KEY_APOSTROPHE;
      m["enter"] = GLFW_KEY_ENTER;

      m["left-shift"] = GLFW_KEY_LEFT_SHIFT;
      m[","] = GLFW_KEY_COMMA;
      m["."] = GLFW_KEY_PERIOD;
      m["/"] = GLFW_KEY_SLASH;
      m["right-shift"] = GLFW_KEY_RIGHT_SHIFT;

      m["left-control"] = GLFW_KEY_LEFT_CONTROL;
      m["left-alt"] = GLFW_KEY_LEFT_ALT;
      m["space"] = GLFW_KEY_SPACE;
      m["right-alt"] = GLFW_KEY_RIGHT_ALT;
      m["right-control"] = GLFW_KEY_RIGHT_CONTROL;

      m["up"] = GLFW_KEY_UP;
      m["down"] = GLFW_KEY_DOWN;
      m["left"] = GLFW_KEY_LEFT;
      m["right"] = GLFW_KEY_RIGHT;

      // missing: numpad, windows key, function key
      return m;
    }
  };

  const map<string, int> controlMap = GlfwControls::get();

  typedef map<int, InputCallback> glfwCommandMap;

  typedef pair<glfwCommandMap, glfwCommandMap> pressReleaseMaps;

  // will get __declspec(dllexport)
  pressReleaseMaps generateInput(map<string, command>* controlCommandMap) {
    glfwCommandMap pressControls;
    glfwCommandMap releaseControls;

    for (auto it = controlCommandMap->begin(); it != controlCommandMap->end(); ++it) {
      string controlName = it->first;
      command command = it->second;
      int glfwCode = controlMap.at(controlName);
      if (command.type == pegcore::PEG_DOWN || command.type == pegcore::PEG_PRESS) {
        pressControls[glfwCode] = command.pressFunc;
      }
      if (command.type == pegcore::PEG_DOWN || command.type == pegcore::PEG_RELEASE) {
        releaseControls[glfwCode] = command.releaseFunc;
      }
    }

    pressReleaseMaps maps = std::make_pair(pressControls, releaseControls);

    return maps;
  }
}