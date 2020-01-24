/*
** EPITECH PROJECT, 2020
** oaefjẑpdiebhivjr
** File description:
** jkmlihukgjfthdrste
*/

#include "intersection.h"

static double calc_delta(point_t nb)
{
    return nb.y * nb.y - 4 * nb.x * nb.z;
}

static point_t eq_sphere(point_t pos, point_t vec, float rad)
{
    point_t equation;

    equation.x = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
    equation.y = 2 * (pos.x * vec.x + pos.y * vec.y + pos.z * vec.z);
    equation.z = (pos.x * pos.x + pos.y * pos.y + pos.z * pos.z) - (rad * rad);
    return equation;
}

static point_t eq_cylinder(point_t pos, point_t vec, float rad)
{
    point_t equation;

    equation.x = vec.x * vec.x + vec.y * vec.y;
    equation.y = 2 * (pos.x * vec.x + pos.y * vec.y);
    equation.z = (pos.x * pos.x + pos.y * pos.y) - (rad * rad);
    return equation;
}

static point_t eq_cone(point_t pos, point_t vec, float angle)
{
    point_t equation;

    float a = angle * M_PI/180;
    equation.x = vec.x * vec.x + vec.y * vec.y - pow(tan(a), 2) * vec.z * vec.z;
    equation.y = 2 * (pos.x * vec.x + pos.y * vec.y - pow(tan(a), 2) * pos.z * vec.z);
    equation.z = pos.x * pos.x + pos.y * pos.y - pow(tan(a), 2);
    return equation;
}

static float *solver(point_t nb)
{
    float *result = malloc(sizeof(float) *  1);

    result[0] = -nb.z/nb.y;
    return result;
}

static float *root(point_t nb)
{
    float *result = malloc(sizeof(float) * 2);

    if (nb.x != 0) {
        result[0] = (-nb.y + sqrt(calc_delta(nb))) / (2 * nb.x);
        result[1] = (-nb.y - sqrt(calc_delta(nb))) / (2 * nb.x);
        return result;
    } else
        return solver(nb);
}

static point_t line(point_t p, point_t v, float t)
{
    point_t l;

    l.x = p.x + (t * v.x);
    l.y = p.y + (t * v.y);
    l.z = p.z + (t * v.z);
    return l;
}

static void display_1_intersection(point_t p, point_t v, float *delta)
{
    point_t l = line(p, v, delta[0]);

    printf("1 intersection point:\n(%.3f, %.3f, %.3f)\n", l.x, l.y, l.z);
}

static void display_2_intersection(point_t p, point_t v, float *delta)
{
    point_t l = line(p, v, delta[0]);
    point_t l_2 = line(p, v, delta[1]);

    printf("2 intersection points:\n(%.3f, %.3f, %.3f)\n"
           "(%.3f, %.3f, %.3f)\n", l.x, l.y, l.z, l_2.x, l_2.y, l_2.z);
}

int sphere(point_t p, point_t v, float rad)
{
    float *delta = malloc(sizeof(*delta) * 2);

    printf("Sphere of radius %.f\n", rad);
    printf("Line passing through the point (%.f, %.f, %.f) and parallel"
           " to the vector (%.f, %.f, %.f)\n", p.x, p.y, p.z, v.x, v.y, v.z);
    if (calc_delta(eq_sphere(p, v, rad)) < 0)
        printf("No intersection point.\n");
    else if (calc_delta(eq_sphere(p, v, rad)) == 0) {
        delta = root(eq_sphere(p, v, rad));
        display_1_intersection(p, v, delta);
    }
    else {
        delta = root(eq_sphere(p, v, rad));
        display_2_intersection(p, v, delta);
    }
    return 0;
}

int cylinder(point_t p, point_t v, float rad)
{
    float *delta = malloc(sizeof(*delta) * 2);

    printf("Cylinder of radius %.f\n", rad);
    printf("Line passing through the point (%.f, %.f, %.f) and parallel"
           " to the vector (%.f, %.f, %.f)\n", p.x, p.y, p.z, v.x, v.y, v.z);
    point_t eq = eq_cylinder(p, v, rad);
    if (eq.x == 0) {
        printf("There is an infinite number of intersection points.\n");
        return 0;
    }
    if (calc_delta(eq_cylinder(p, v, rad)) < 0)
        printf("No intersection point.\n");
    else if (calc_delta(eq_cylinder(p, v, rad)) == 0) {
        delta = root(eq_cylinder(p, v, rad));
        display_1_intersection(p, v, delta);
    }
    else {
        delta = root(eq);
        display_2_intersection(p, v, delta);
    }
    return 0;
}

int cone(point_t p, point_t v, float rad)
{
    float *delta = malloc(sizeof(*delta) * 2);

    printf("Cone with a %.f degree angle\n", rad);
    printf("Line passing through the point (%.f, %.f, %.f) and parallel"
           " to the vector (%.f, %.f, %.f)\n", p.x, p.y, p.z, v.x, v.y, v.z);
    if (calc_delta(eq_cone(p, v, rad)) < 0)
        printf("No intersection point.\n");
    else if (calc_delta(eq_cone(p, v, rad)) == 0) {
        delta = root(eq_cone(p, v, rad));
        display_1_intersection(p, v, delta);
    }
    else {
        delta = root(eq_cone(p, v, rad));
        display_2_intersection(p, v, delta);
    }
    return 0;
}

int intersection(int ac, char **av)
{
    point_t point = {atof(av[2]), atof(av[3]), atof(av[4])};
    point_t vector = {atof(av[5]), atof(av[6]), atof(av[7])};

    switch (av[1][0]) {
    case '1':
        return sphere(point, vector, atof(av[8]));
    case '2':
        return cylinder(point, vector, atof(av[8]));
    case '3':
        return cone(point, vector, atof(av[8]));
    default:
        return 84;
    }
}
