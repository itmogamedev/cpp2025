#include <iostream>
#include "..\StaticLib2\vec3.h"
#include <Vector>

#include <iostream>
#include <cassert>
#include <cmath>

#include <limits>
#include <string>



// ─── Утилиты
// ──────────────────────────────────────────────────────────────────

void clearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pause() {
  std::cout << "\nPress Enter for continue...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printSeparator(char c = '-', int n = 45) {
  std::cout << std::string(n, c) << "\n";
}

// ─── Ввод вектора
// ─────────────────────────────────────────────────────────────

Vec3 inputVector(const std::string& name) {
  double x, y, z;
  std::cout << "  Enter components vector's " << name << ":\n";
  while (true) {
    std::cout << "    x: ";
    std::cin >> x;
    std::cout << "    y: ";
    std::cin >> y;
    std::cout << "    z: ";
    std::cin >> z;
    if (std::cin) break;
    std::cout << "  [!] Invalid input. Please try again.\n";
    clearInput();
  }
  clearInput();
  return Vec3(x, y, z);
}

// ─── Меню управления векторами
// ────────────────────────────────────────────────

void menuSetVectors(Vec3& A, Vec3& B) {
  int choice;
  while (true) {
    printSeparator();
    std::cout << "Current vectors:\n";
    std::cout << "    A = " << A << "\n";
    std::cout << "    B = " << B << "\n";
    printSeparator();
    std::cout << "  1. Edit vector A\n";
    std::cout << "  2. Edit vector B\n";
    std::cout << "  3. Edit both vectors\n";
    std::cout << "  0. Back\n";
    printSeparator();
    std::cout << "Choise: ";
    std::cin >> choice;
    clearInput();

    switch (choice) {
      case 1:
        A = inputVector("A");
        break;
      case 2:
        B = inputVector("B");
        break;
      case 3:
        A = inputVector("A");
        B = inputVector("B");
        break;
      case 0:
        return;
      default:
        std::cout << "Answer Choise!\n";
    }
  }
}

// ─── Операции ────────────────────────────────────────────────────────────────

void opAdd(const Vec3& A, const Vec3& B) {
  std::cout << "\n  " << A << "  +  " << B << "\n";
  std::cout << "  = " << (A + B) << "\n";
}

void opSub(const Vec3& A, const Vec3& B) {
  std::cout << "\n  " << A << "  -  " << B << "\n";
  std::cout << "  = " << (A - B) << "\n";
}

void opScale(const Vec3& A) {
  double s;
  std::cout << "Enter scalar: ";
  std::cin >> s;
  clearInput();
  std::cout << "\n  " << A << "  *  " << s << "\n";
  std::cout << "  = " << (A * s) << "\n";
}

void opDot(const Vec3& A, const Vec3& B) {
  std::cout << "\n  " << A << "  ·  " << B << "\n";
  std::cout << "  = " << A.dot(B) << "\n";
}

void opCross(const Vec3& A, const Vec3& B) {
  std::cout << "\n  " << A << "  ×  " << B << "\n";
  std::cout << "  = " << A.cross(B) << "\n";
}

void opLength(const Vec3& A) {
  std::cout << "\n  |" << A << "| = " << A.length() << "\n";
}

void opNormalize(const Vec3& A) {
  try {
    Vec3 n = A.normalize();
    std::cout << "\n  norm(" << A << ")\n";
    std::cout << "  = " << n << "\n";
    std::cout << "Length check: " << n.length() << "\n";
  } catch (const std::runtime_error& e) {
    std::cout << "\nError!: " << e.what() << "\n";
  }
}

// ─── Меню операций
// ────────────────────────────────────────────────────────────

void menuOperations(Vec3& A, Vec3& B) {
  int choice;
  while (true) {
    printSeparator();
    std::cout << "  A = " << A << "\n";
    std::cout << "  B = " << B << "\n";
    printSeparator('=');
    std::cout << "Operations\n";
    printSeparator();
    std::cout << "  1. A + B\n";
    std::cout << "  2. A - B\n";
    std::cout << "  3. Multi on scalar  A * s\n";
    std::cout << "  4. Scalar's multi A · B\n";
    std::cout << "  5. Vector's multi A × B\n";
    std::cout << "  6. Length vector A\n";
    std::cout << "  7. Normal vector A\n";
    std::cout << "  0. Back\n";
    printSeparator();
    std::cout << "Choise: ";
    std::cin >> choice;
    clearInput();

    switch (choice) {
      case 1:
        opAdd(A, B);
        break;
      case 2:
        opSub(A, B);
        break;
      case 3:
        opScale(A);
        break;
      case 4:
        opDot(A, B);
        break;
      case 5:
        opCross(A, B);
        break;
      case 6:
        opLength(A);
        break;
      case 7:
        opNormalize(A);
        break;
      case 0:
        return;
      default:
        std::cout << "Answer choise!\n";
        continue;
    }
    pause();
  }
}

// ─── Главное меню
// ─────────────────────────────────────────────────────────────

int main() {
  Vec3 A(1.0, 0.0, 0.0);
  Vec3 B(0.0, 1.0, 0.0);

  int choice;
  while (true) {
    printSeparator('=');
    std::cout << "VEC3 CALCULATOR\n";
    printSeparator('=');
    std::cout << "  A = " << A << "\n";
    std::cout << "  B = " << B << "\n";
    printSeparator();
    std::cout << "  1. Set vectors\n";
    std::cout << "  2. Execute operation\n";
    std::cout << "  0. Exit\n";
    printSeparator();
    std::cout << "Choise:";
    std::cin >> choice;
    clearInput();

    switch (choice) {
      case 1:
        menuSetVectors(A, B);
        break;
      case 2:
        menuOperations(A, B);
        break;
      case 0:
        std::cout << "\n  Goodby!\n";
        return 0;
      default:
        std::cout << "Answer Choise!\n";
    }
  }
}