#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include <ostream>
#include <random>
#include <vector>
#include "player.h"

namespace lucas {

    class DerandomTurboPlayer : public Player {

        /* We will classify each player using quantiles.
         * Break the universe of possible guesses into four equal quantiles.
         * For each guess that falls into either the first or the last quantile,
         * increment the attritue 'external'.
         * For each guess that falls into either the second or third quantile,
         * increment the attribute 'internal'.
         *
         * If the number of internal guesses is "far greater than"
         * the number of external guesses,
         * we will consider that the player uses a gaussian algorithm.
         * Otherwise, we will consider that the player is completely random.
         *
         * We use double because a guess might fall "between" two classes.
         * For instance, with six chopsticks, the quantiles are
         * [0, 1.5], [1.5, 3], [3, 4.5], [4.5, 6].
         * In this case, we will add a guess half to one quantile
         * and half to the other.
         */
        struct quantile {
            double external;
            double internal;
            bool already_played = false;
            bool is_gaussian() const;
        };
        
        std::mt19937 rng;
        std::string _name;
        int my_index;
        int my_hand;
        std::ostream * _os;

        /* If keep() is true, this player will keep the statistics between games.
         */
        bool keep;

        /* Number of gaussian/pure random players. */
        int gaussian_count;
        int random_count;
        void compute_counts();

        std::vector< quantile > quantiles;

        /* Returns a new random number with maximum value 'max'.
         * The distribution of this random number is uniform.
         *
         * For instance, random(1) generates a boolean.
         */
        int random( int max );

    public:
        DerandomTurboPlayer(
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

} // namespace random_player

#endif // RANDOM_PLAYER_H
