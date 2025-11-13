int main() {
    float a_length;
    float b_length;
    float height_length;
    float s;

    std::cout << "Type a-side length" << std::endl;
    std::cin >> a_length;
    std::cout << "Type b-side length" << std::endl;
    std::cin >> b_length;
    std::cout << "Type height length" << std::endl;
    std::cin >> height_length;

    s = (a_length + b_length) / 2 * height_length;

    std::cout << "S = " << s << std::endl;
}