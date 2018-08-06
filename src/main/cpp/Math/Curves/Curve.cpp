namespace Curves::Math
{
    class Curve
    {
        public:
        Curve(){}
        virtual ~Curve(){}
        virtual Math::Vector2 getValue(float t) = 0;
        virtual float getValueInverse(Math::Vector2 point) = 0;
        virtual float getDerivative(float t) = 0;
        virtual float getNearestPoint(Math::Vector2 point) = 0;
        virtual float getLength(float t) = 0;
    };
}