#ifndef DEZERO_PLAYER_H
#define DEZERO_PLAYER_H

#include <ostream>
#include <random>
#include <vector>
#include "player.h"

namespace lucas {

    class DezeroPlayer : public Player {

        int my_index;
        int my_hand;
        std::ostream * _os;

        /* If keep() is true, this player will keep the statistics between games.
         */
        bool keep;

        std::mt19937 rng;
        std::string _name;
        int r;
        double stats;

        /* Returns a new random number with maximum value 'max'.
         * The distribution of this random number is uniform.
         *
         * For instance, random(1) generates a boolean.
         */
        int random( int max );
        void compute_stats();

    public:
        DezeroPlayer(
            unsigned long long seed,
            std::string name,
            bool keep
        );

        /* Sets/gets the output stream of this player.
         * Default output stream: royer::null_stream.
         */
        void out( std::ostream& );
        std::ostream& out();

        std::string name() const override;
        void begin_game() override;
        int hand() override;
        int guess() override;
        void end_round() override;
        void end_game() override;
    };

} // namespace lucas

#endif // DEZERO_PLAYER_H
