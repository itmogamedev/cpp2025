#pragma once

#include <cmath>
#include <iostream>
#include <stdexcept>

/**
 * @brief Структура трёхмерного вектора
 */
struct Vec3 {
  double x, y, z;

  // ─── Конструкторы ────────────────────────────────────────────────────────
  Vec3() : x(0.0), y(0.0), z(0.0) {}
  Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

  // ─── Сложение / вычитание ────────────────────────────────────────────────

  /** Возвращает сумму двух векторов */
  Vec3 add(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  /** Возвращает разность двух векторов */
  Vec3 sub(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  // ─── Умножение на скаляр ─────────────────────────────────────────────────

  /** Возвращает вектор, умноженный на скаляр */
  Vec3 scale(double scalar) const {
    return {x * scalar, y * scalar, z * scalar};
  }

  // ─── Скалярное произведение ───────────────────────────────────────────────

  /** Возвращает скалярное произведение двух векторов */
  double dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
  }

  // ─── Векторное произведение ───────────────────────────────────────────────

  /** Возвращает векторное произведение (this × other) */
  Vec3 cross(const Vec3& other) const {
    return {y * other.z - z * other.y, z * other.x - x * other.z,
            x * other.y - y * other.x};
  }

  // ─── Длина и нормализация ─────────────────────────────────────────────────

  /** Возвращает длину (модуль) вектора */
  double length() const { return std::sqrt(x * x + y * y + z * z); }

  /**
   * @brief Возвращает единичный вектор (нормализованный).
   * @throws std::runtime_error если длина вектора равна нулю.
   */
  Vec3 normalize() const {
    double len = length();
    if (len == 0.0)
      throw std::runtime_error("Нельзя нормализовать нулевой вектор");
    return {x / len, y / len, z / len};
  }

  // ─── Перегруженные операторы ──────────────────────────────────────────────

  /** Сложение векторов: a + b */
  Vec3 operator+(const Vec3& other) const { return add(other); }

  /** Вычитание векторов: a - b */
  Vec3 operator-(const Vec3& other) const { return sub(other); }

  /** Умножение вектора на скаляр: v * s */
  Vec3 operator*(double scalar) const { return scale(scalar); }

  /** Сравнение векторов */
  bool operator==(const Vec3& other) const {
    return x == other.x && y == other.y && z == other.z;
  }
};

/** Умножение скаляра на вектор: s * v */
inline Vec3 operator*(double scalar, const Vec3& v) { return v * scalar; }

/** Вывод вектора в поток: << */
inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
  os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
  return os;
}