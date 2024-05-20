#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "railroad.h"
typedef struct City
{
    char *name;
    struct Road **roads;
    int road_count;
} *City;

typedef struct Road
{
    City start, destination;
    float *wear;
    int wear_count;
} *Road;

typedef struct Map
{
    City *cities;
    int city_count;
} *Map;

float max(float a, float b)
{
    return a > b ? a : b;
};
int main()
{
    Map mapa = malloc(sizeof(struct Map));
    int num_cities = 3;
    mapa->cities = malloc(num_cities * sizeof(City));
    mapa->city_count = num_cities;

    for (int i = 0; i < num_cities; i++)
    {
        mapa->cities[i] = malloc(sizeof(struct City));
        mapa->cities[i]->roads = NULL;
        mapa->cities[i]->road_count = 0;
    }

    mapa->cities[0]->name = "City1";
    mapa->cities[1]->name = "City2";
    mapa->cities[2]->name = "City3";
    Road road1 = malloc(sizeof(struct Road));
    road1->start = mapa->cities[0];
    road1->destination = mapa->cities[1];
    road1->wear = malloc(3 * sizeof(float));
    road1->wear[0] = 0.3;
    road1->wear[1] = 0.5;
    road1->wear[2] = 0.7;
    road1->wear_count = 3;
    mapa->cities[0]->roads = realloc(mapa->cities[0]->roads, (mapa->cities[0]->road_count + 1) * sizeof(Road));
    mapa->cities[0]->roads[mapa->cities[0]->road_count] = road1;
    mapa->cities[0]->road_count++;
    road1->wear[0] = 0;
    road1->wear[1] = 0.2;
    road1->wear[2] = 0.6;
    mapa->cities[1]->roads = realloc(mapa->cities[1]->roads, (mapa->cities[1]->road_count + 1) * sizeof(Road));
    mapa->cities[1]->roads[mapa->cities[1]->road_count] = road1;
    mapa->cities[1]->road_count++;

    // update wear
    for (int n = 0; n < 5; n++)
    {
        for (int i = 0; i < mapa->city_count; i++)
        {
            City start = mapa->cities[i];
            for (int j = 0; j < start->road_count; j++)
            {
                float tmp_wear[start->roads[j]->wear_count];
                for (int k = 0; k < start->roads[j]->wear_count; k++)
                {
                    tmp_wear[k] = start->roads[j]->wear[k];
                }
                City destination = start->roads[j]->destination;
                for (int k = 0; k < start->roads[j]->wear_count; k++)
                {
                    if (start->roads[j]->wear_count == 1)
                    {
                        // if the road has only one wear value
                        if (start->roads[j]->wear[0] != 0)
                        {
                            tmp_wear[0] *= 2;
                        }
                        else if (start->roads[j]->wear[0] == 0)
                        {
                            float max_dest = 0;
                            float max_start = 0;
                            for (int l = 0; l < destination->road_count; l++)
                            {
                                if (destination->roads[l]->wear[0] > max_dest)
                                {
                                    max_dest = destination->roads[l]->wear[0];
                                }
                            }
                            for (int l = 0; l < start->road_count; l++)
                            {
                                if (l == j)
                                {
                                    continue;
                                }
                                if (start->roads[l]->wear[start->roads[l]->wear_count] > max_start)
                                {
                                    max_start = start->roads[l]->wear[start->roads[l]->wear_count];
                                }
                            }
                            tmp_wear[0] = max(max_start, max_dest);
                        }
                    }
                    else if (start->roads[j]->wear[k] == 0 && k == start->roads[j]->wear_count - 1)
                    {
                        float max_dest = 0;
                        for (int l = 0; l < destination->road_count; l++)
                        {
                            if (destination->roads[l]->wear[0] > max_dest)
                            {
                                max_dest = destination->roads[l]->wear[0];
                            }
                        }
                        tmp_wear[k] = max(max_dest, start->roads[j]->wear[k - 1]);
                    }
                    else if (start->roads[j]->wear[k] == 0 && k == 0)
                    {
                        float max_start = 0;
                        for (int l = 0; l < start->road_count; l++)
                        {
                            if (l == j)
                            {
                                continue;
                            }
                            if (start->roads[l]->wear[start->roads[l]->wear_count - 1] > max_start)
                            {
                                max_start = start->roads[l]->wear[start->roads[l]->wear_count];
                            }
                        }
                        tmp_wear[0] = max(max_start, start->roads[j]->wear[1]);
                    }
                }
            }
        }
    }
