#pragma once
#include "engine/Graphics.hpp"
#include "util/Rand.hpp"
#include <SDL3/SDL.h>

class Sketch {
public:
  virtual ~Sketch() = default;
  virtual void Setup() {};
  virtual void Update(float dt) { (void)dt; };
  virtual void Draw() = 0;
  virtual void OnEvent(const SDL_Event &e) { (void)e; };

  void Background(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_Graphics->Background(r, g, b, a);
  }

  void Line(float x1, float y1, float x2, float y2) {
    m_Graphics->Line(x1, y1, x2, y2);
  }

  void Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_Graphics->Color(r, g, b, a);
  }

  void Stroke(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
    m_Graphics->Color(r, g, b, a);
  }

  void StrokeWeight(int weight) { m_Graphics->StrokeWeight(weight); }

  void Circle(float x, float y, float radius) {
    m_Graphics->Circle(x, y, radius);
  }

  void PointSize(int value) { m_Graphics->PointSize(value); }

  void Circle(int x, int y, float radius) { m_Graphics->Circle(x, y, radius); }

  void Rect(float x, float y, float width, float height) {
    m_Graphics->Rect(x, y, width, height);
  }

  void Rect(float x, float y, float width) {
    m_Graphics->Rect(x, y, width, width);
  }

  void Point(float x, float y) { m_Graphics->Point(x, y); }

  int Rand(int min, int max) { return util::random::rand_int(min, max); }
  int Rand(int max) { return util::random::rand_int(max); }
  double Rand(double min, double max) {
    return util::random::rand_real(min, max);
  }
  double Rand(double max) { return util::random::rand_real(max); }
  void RandomSeed(std::uint64_t seed) { util::random::seed(seed); }

  int Width() { return m_Graphics->Width(); }

  int Height() { return m_Graphics->Height(); }

protected:
  Graphics &G() { return *m_Graphics; };
  Graphics &p5() { return *m_Graphics; };

private:
  friend class Canvas;
  Graphics *m_Graphics = nullptr;
};
