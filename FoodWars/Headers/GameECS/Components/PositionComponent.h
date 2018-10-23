
class PositionComponent {
public:
    int X;
    int Y;
    PositionComponent();
    PositionComponent(int x, int y);
    PositionComponent& operator+=(const PositionComponent& other);
    PositionComponent& operator--(int);
};