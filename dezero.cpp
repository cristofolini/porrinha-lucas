#include <ostream>
#include "stdlib.h"
#include "core/util.h"
#include "dezero.h"
#include "porrinha-royer/nullstream.h"

namespace lucas {

    DezeroPlayer::DezeroPlayer(
            unsigned long long seed,
            std::string name,
            bool keep
    ) :
        rng(seed),
        keep(keep),
        _name(name),
        _os( &royer::null_stream )
    {}

    int DezeroPlayer::random( int max ) {
        return std::uniform_int_distribution<int>(0, max)( rng );
    }

    void DezeroPlayer::compute_stats() {
        for( int i = 0; i < core::player_count(); i++ ) {
            if( i == my_index )
                continue;
            if( core::guess(i) == core::NOT_PLAYING )
                continue;
       }
    }

    void DezeroPlayer::out( std::ostream& os ) {
        _os = &os;
    }

    std::ostream& DezeroPlayer::out() {
        return *_os;
    }


    std::string DezeroPlayer::name() const {
        return _name;
    }

    void DezeroPlayer::begin_game() {
        my_index = core::index(this);
        stats = 0;
        r = 0;
        /*if( !keep || quantiles.size() != core::player_count() )
            quantiles = std::vector<quantile>(core::player_count());*/
    }

    int DezeroPlayer::hand() {
        if( stats == 0 && r ==0 ) {
            /* No data information. Let's be pure random. */
            out() << "[dezero]: no info, pure random move.\n";
            my_hand = random(core::chopsticks(my_index));
            if(rand()%100<5) {
                my_hand = rand()%core::chopsticks(core::index(this))+1;
            }
        }
        /*else if( stats == 0 ) {
            /* No stats. Let's try to push the final number
             * as close to the mean as possible,
             * so that we may guess right, while the others will guess randomly.
             *
            out() << "[dezero]: Gaussian move\n";
            my_hand = core::chopsticks(my_index)/2;
        }*/
        else {
            out() << "[dezero]: Stats acquired. Pondered move.\n";
            my_hand = core::chopsticks(my_index) - (int)stats;
            if(rand()%100<5 || my_hand < 0) {
                my_hand = rand()%core::chopsticks(core::index(this))+1;
            }
        }

        return my_hand;
    }

    int DezeroPlayer::guess() {
        /* Guess algorithm chosen arbitrarily.
         *
         * The player will begin by guessing the central value,
         * then central + 1, central - 1, central + 2, central - 2, etc.
         */
         
         int guess;
            int min = my_hand;
            int max = core::chopstick_count() - core::chopsticks(my_index) + my_hand + (int)stats;
            guess = (max + min) / 2;
            int shift = 1;
            while( !core::valid_guess(guess) ) {
                guess += shift;
                shift = - 1 - shift;
            }
        return guess;

    }

    void DezeroPlayer::end_round() {
        for( int i = 0; i < core::player_count(); i++ ) {
            if( i == my_index )
                continue;
            if( core::guess(i) < 0 )
                continue;
            r++;
            stats = (stats + core::guess(i)) / r;
            double half = core::chopstick_count() / 2.0;
            /*int guess = core::guess(i);
            double dist = std::fabs( half - guess ) / half;
            /* dist is 0 if half == guess,
             * and 1 if guess == 0 or guess == max. */
        }
    }

    void DezeroPlayer::end_game() {
        // no-op
    }

} // namespace lucas
