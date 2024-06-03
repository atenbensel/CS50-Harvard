#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX 9

typedef struct
{
    const char *name;
    int votes;
}
candidate;

candidate candidates[MAX];
int candidate_count;

bool vote(const char *name);
void print_winner(void);

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    for (int i =0; i < voter_count; i++)
    {
        const char *name = get_string("Vote: ");
        if (!vote(name))
        {
            printf("Invalid vote for candidate: %s\n", name);
        }
    }
    print_winner();
}

bool vote(const char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    int maximum_vote = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > maximum_vote)
        {
            maximum_vote = candidates[i].votes;
        }
    }

    if (maximum_vote == 0)
    {
        printf("No votes cast\n");
        return;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == maximum_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
