#include <iostream>
#include "Vectors.h"

int main()
{
    vectors a(1.f, 2.f, 3.f);
    vectors b(4.f, 5.f, 6.f);

    vectors c = a + b;
    std::cout << "Summary:" << c << std::endl;

    std::cout << "x = " << c.get_x() << std::endl;
    std::cout << "y = " << c.get_y() << std::endl;
    std::cout << "z = " << c.get_z() << std::endl;

    vectors d = a - b;
    std::cout << "Subtraction:" << d << std::endl;

    vectors e = 2 * a;
    std::cout << "Product out of 2: " << e << std::endl;

    float scalar = a.sc_prod(a, b);
    std::cout << "Scalar product: " << scalar << std::endl;
    return 0;
}
