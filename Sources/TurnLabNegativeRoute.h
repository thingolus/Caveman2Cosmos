#ifndef TURNLAB_NEGATIVE_ROUTE_H
#define TURNLAB_NEGATIVE_ROUTE_H

// Candidate source default; command-line0 supports an independent compile-off check.
#ifndef TURNLAB_NEGATIVE_GENERAL_ROUTE
#define TURNLAB_NEGATIVE_GENERAL_ROUTE 1
#endif

#if TURNLAB_NEGATIVE_GENERAL_ROUTE
namespace TurnLabNegativeRoute
{
    unsigned int stableGeneration();
    bool hit(int player, int team, unsigned int generation);
    void remember(int player, int team, unsigned int generation);
    void disableForLiveDefinitionEdit();
    bool beginMutation();
    void endMutation();
    class Mutation
    {
    public:
        Mutation() : armed(beginMutation()) {}
        ~Mutation() { if (armed) endMutation(); }
    private:
        bool armed;
        Mutation(const Mutation&);
        Mutation& operator=(const Mutation&);
    };
    class DefinitionMutation
    {
    public:
        explicit DefinitionMutation(bool finalInitialized)
        { if (finalInitialized) disableForLiveDefinitionEdit(); }
    private:
        Mutation mutation;
        DefinitionMutation(const DefinitionMutation&);
        DefinitionMutation& operator=(const DefinitionMutation&);
    };
}
#define TL_NEG_ROUTE_DEFINITION_MUTATION(name) TurnLabNegativeRoute::DefinitionMutation name(GC.getGamePointer() != NULL && GC.getGame().isFinalInitialized())
#define TL_NEG_ROUTE_MUTATION(name) TurnLabNegativeRoute::Mutation name
#else
#define TL_NEG_ROUTE_DEFINITION_MUTATION(name)
#define TL_NEG_ROUTE_MUTATION(name)
#endif
#endif
