namespace Math
{
    inline float Lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

    inline float LerpInverse(float a, float b, float v)
    {
        return (v - a) / (b - a);
    }

    inline float Clamp(float min, float max, float v)
    {
        return (v > max) ? max : ((v < min) ? min : v);
    }

    const float PI = 3.14159265359;
}