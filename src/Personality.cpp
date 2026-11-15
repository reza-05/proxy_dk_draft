#include "Personality.h"
#include <random>
#include <chrono>
#include <vector>

namespace ProxyMystery {

static int getVariant(int count) {
    static std::mt19937 rng(std::random_device{}() ^ 
        static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(0, count - 1);
    return dist(rng);
}

std::string Personality::formatDialogue(Archetype archetype, QuestionTopic topic,
                                      const std::string& location, const std::string& witness,
                                      bool isLie, const std::string& proxyKingName) {
    int v = getVariant(3);
    std::string response;

    switch (archetype) {
        case Archetype::CR:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                if (isLie) {
                    const std::string lies[] = {
                        "Ami to " + location + ", pechoner ke ki korse ami shamne theke bujhbo kemne?",
                        "Bhai ami " + location + ", shobai ke manage korte giye pechone kheyal kori nai.",
                        "Arey ami " + location + " chilam, roll call e ami kono extra response dei nai!"
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Ami first row te " + location + ", nijer roll call e 'Present sir' bolsilam.",
                        "CR hoye ami shuru thekei podium er pashe " + location + ", shobai dekhse.",
                        "Ami to first bench e " + location + ", register er dike kheyal rakhsilam."
                    };
                    response = truths[v];
                }
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                if (isLie) {
                    const std::string lies[] = {
                        "Amar kache shob shobdor daak normal lagse, tobe " + witness + " ektu nervous chilo.",
                        "Ami to CR, shobai k dekhtesilam, tobe " + witness + " er dik theke ektu chapa shur ashsilam.",
                        "Pechone " + witness + " ar or gang ghurgur kortesilo, tader e jera koro."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Sir jokhon matha nichu kore roll daktesilo, pechoner row theke ek e golar shure 2-3 bar 'Yes sir' ashse!",
                        "Pechon theke ekjoner golay 2 bar 'Present sir' shunlam, roll 45 par howar shomoy.",
                        "Roll call er shomoy pechoner bench e ektu fush-fush shobdo hoitesilo, nishchoi voice imitation!"
                    };
                    response = truths[v];
                }
            } else {
                const std::string alibis[] = {
                    "First row er shobai ke jiges koro, ami nijer roll chara kono extra daak dei nai.",
                    "Sir er table er shamne " + witness + " chilo, o bolte parbena ami voice change korsi.",
                    witness + " nijei dekhse ami podium er kache shuru thekei darano chilam."
                };
                response = alibis[v];
            }
            break;

        case Archetype::BACKBENCHER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                if (isLie) {
                    const std::string lies[] = {
                        "Arey mama, ami to " + location + ". Kono extra roll call e ami daak dei nai!",
                        "Bhai shune laabh nai, ami " + location + ", pechone ke kar shobdo imitation korse ami jani na.",
                        "Mama ami to " + location + " chilam, amar roll er shomoy ami nijei 'Present' bolsi."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Mama ami shanti moto " + location + ", kono jhamelay chilam na.",
                        "Arey bhai ami to last bench e " + location + ", phone e notification check kortesilam.",
                        "Pechone " + location + " chill kortesilam mama, sir er daak shune shudhu nijer ta disi."
                    };
                    response = truths[v];
                }
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                if (isLie) {
                    const std::string lies[] = {
                        "Amra to pechone phone chalaitsilam, sir roll dakse amra nijer ta disi, baki k ki bolse jani na.",
                        "Mama amra backbencher bole shob dosh amader? " + witness + " k jiga o ki kortesilo!",
                        "Bhai ami to game e busy chilam, pashe " + witness + " naki onner proxy daak ditsilo shunlam."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Mama, " + proxyKingName + " er dike ektu takao. O roll call er shomoy voice change kore onner roll e 'Present sir' bolsilo!",
                        "Amar pashe boshe ke jani gala fulaia voice change kore 'Present sir' bole dilo!",
                        "Mama ekjoner golay 2-3 bar roll call shuna gese, amar shondeho " + proxyKingName + " er upor!"
                    };
                    response = truths[v];
                }
            } else {
                const std::string alibis[] = {
                    "Pechoner bench e " + witness + " chilo, jiges koro ami voice change korsilam kina.",
                    "Last row er polarpan jane ami shanti priyo manush, " + witness + " er kache shuno.",
                    "Bhai amar pashe boshe shobai dekhse ami shudhu nijer ta bole chill kortesilam."
                };
                response = alibis[v];
            }
            break;

        case Archetype::TOPPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                if (isLie) {
                    const std::string lies[] = {
                        "Ami to " + location + " ektu theory bujhtesilam, pechone ke daak dise kheyal kori nai.",
                        "Shotti bolte ami roll call er thik age " + location + ", tai class e ektu hurried chilam.",
                        "Ami " + location + " chilam, lab niye tension e chilam tai shobar daak kheyal kori nai."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Ami shokal 8:00 tar age thekei 302 er first row te " + location + ".",
                        "Ami to shuru thekei first bench e chilam, " + location + ". Shobai dekhse.",
                        "Arey bhai, ami to " + location + ". Amar attendance e kono shondeho thakar kotha na."
                    };
                    response = truths[v];
                }
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                if (isLie) {
                    const std::string lies[] = {
                        "Ami lab e busy chilam, tobe " + witness + " roll call er shomoy ektu suspicious lagtesilo.",
                        "Class er shobai to nijer ta ditsilo, kintu " + witness + " er dik theke ektu chapa shur ashsilam.",
                        "Amar mone hoi " + proxyKingName + " kichu ekta lukaitese, or chokhe chokh rakhle bujhte parba."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Sir matha nichu kore roll call korar shomoy pechon theke 2 ta voice imitation shunsilam! Hall er absent cheleder roll dhorsilo!",
                        "Sir jokhon register e sign kortesilo, pechon theke ekjoner golay duibar response ashse!",
                        "Shotti bolte roll call er shomoy " + proxyKingName + " ektu nervous bhabe daak ditsilo, pechoner shobar kheyal chilo."
                    };
                    response = truths[v];
                }
            } else {
                const std::string alibis[] = {
                    "First row er shobai jane ami shuru thekei code kortesilam, onner roll e daak dite jabo kon dukkhe?",
                    "Sir er table er shamne " + witness + " chilo, o dekhse ami first bench e boshe chilam.",
                    "First bench er jare iccha jiges koro, ami nijer roll call chara kothao ekta shobdo kori nai."
                };
                response = alibis[v];
            }
            break;

        case Archetype::SLEEPER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                if (isLie) {
                    const std::string lies[] = {
                        "*Hai tule* Bhai... ami mone hoi " + location + " chilam... thik mone porhtese na.",
                        "Ghum er ghore thik mone nai, tobe ami bodh hoy " + location + " chilam...",
                        "Mama ami adho-ghume chilam, mone hoi " + location + " chilam jokhon sir roll call dakhse."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "*Hai tule* Mama ami 302 te " + location + " matha niche diye ghumaitesilam.",
                        "*Chokh moshe* Bhai... ami shuru thekei bench e " + location + ", AC er haway pura nithor chilam.",
                        "Bhai amar to chokh khultesilo na, ami desk e " + location + " chilam."
                    };
                    response = truths[v];
                }
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                if (isLie) {
                    const std::string lies[] = {
                        "Ami to ghum e chilam bhai, ke kar roll e 'Yes sir' bolse amar ki daay?",
                        "*Hai tule* Bhai amake ghumate dao, " + witness + " re jiges koro o ki shob kortesilo.",
                        "Amar mone hoy " + witness + " ar tar squad eshob proxy call er plan korsilo."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Adho-ghume chokh khule dekhsilam amar pasher chele ta voice change kore arekjon er 'Present sir' bole dilo!",
                        "*Chokh ghoshte ghoshte* Ghumer moddhe shunlam ke jani gala dabaya 2 jon er 'Yes sir' dakhse!",
                        "Amar pashe boshe ke jani churi kore onner roll dhorse, amar ghum e break porchilo oita shune!"
                    };
                    response = truths[v];
                }
            } else {
                const std::string alibis[] = {
                    "*High tulte tulte* " + witness + " re jiga, or dhakkay amar ghum bhaangsilo.",
                    "Mama amar pashe " + witness + " chilo, o jane ami ghum chara kichui kori nai.",
                    "Pechoner bench e jara chilo shobai jane ami class shuru thekei bench e ghum!"
                };
                response = alibis[v];
            }
            break;

        case Archetype::LATECOMER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                if (isLie) {
                    const std::string lies[] = {
                        "Ami to " + location + ", tai class shuru howar 5 minute pore 302 te dhuksi.",
                        "Rasta te ektu jhamela chilo bhai, ami " + location + ", tai ektu piche pore gesilam.",
                        "Bhai ami to " + location + " chilam, dauraia ashte ashte roll call pray shesh hoye ashsilam."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Boardbazar jam e bus atkay gesilo! Ami dauraia 302 te dhuksi jokhon " + location + "!",
                        "Shokal 7:30 er bus miss hoisilo bhai! Ami dauraia eshe " + location + "!",
                        "Bhai Gazipur theke ashte jam e porhsilam, roll call shuru howar thik age " + location + "!"
                    };
                    response = truths[v];
                }
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                if (isLie) {
                    const std::string lies[] = {
                        "Ami to matro dhuklam bhai, ami ashar agei shob roll call shesh!",
                        "Bhai ami to shobari sheshe ashsi, amar age " + witness + " ki korse ami kemne bolbo?",
                        "Amar mone hoi dorjar kache " + witness + " daraye eishob fake daak manipulate kortesilo."
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Ami dorja diye dhukar shomoy e shunlam amar roll call er age ke jani pechon theke fake 'Yes sir' bole felse!",
                        "Ami class e matro dhuktesi, shunlam pechon theke kar jani throat cough diye duplicate voice e 'Present' dakhse!",
                        "Dorja theke dhukei dekhlam " + proxyKingName + " chapa hashite onner fake roll count kortese!"
                    };
                    response = truths[v];
                }
            } else {
                const std::string alibis[] = {
                    witness + " nije dekhse ami shobari sheshe dauraia 302 te dhuksi!",
                    "Dorjay jara darano chilo, tader jiga ami matro hall theke hete ashsi.",
                    witness + " re jiges koro, ami dorjay ashlei sir bolse 'taratari bosh'."
                };
                response = alibis[v];
            }
            break;

        case Archetype::GOSSIP_MASTER:
            if (topic == QuestionTopic::LOCATION_DURING_ROLLCALL) {
                if (isLie) {
                    const std::string lies[] = {
                        "Ami to " + location + " chilam, kintu eta kintu ami bolinai!",
                        "Shuno, ami " + location + " ekjoner shathe kotha boltisilam, pechoner shobdo ami shuninai!",
                        "Ami to " + location + " chilam ektu, kintu roll call er shomoy nijer bench ei boshsilam!"
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Ami 302 er majhkhaner row te " + location + ", shobai ke k ashse dekhsilam.",
                        "Ami to row 3 te boshe " + location + ", dorja diye ke k dhukse shob count korsilam!",
                        "Shuru thekei ami 302 te " + location + ", kar koto attendance lagbe hishab kortesilam."
                    };
                    response = truths[v];
                }
            } else if (topic == QuestionTopic::SUSPICIOUS_ACTIVITY) {
                if (isLie) {
                    const std::string lies[] = {
                        "Shunsilam " + witness + " naki hall er friend der proxy dewar kotha ditsilo, ami nishchit na kintu!",
                        "Amar mone hoy " + witness + " eishob shobdo imitation korar practice kortesilo piche!",
                        "Ogo jiges koro na, " + witness + " ar or pasher group ekhon shanto saje boshe ache!"
                    };
                    response = lies[v];
                } else {
                    const std::string truths[] = {
                        "Shuno, hall theke 3 jon ashei nai ajke, kintu roll call e tader response ashse! Oita nishchoi gang er kaaj.",
                        "Amar kaan bohut sharp! Pechoner bench theke ekjon voice change kore 5 tar proxy dise, ami sure!",
                        "Eita ekdom confidential khobor: " + proxyKingName + " naki sokal thekei proxy syndicate chalaise!"
                    };
                    response = truths[v];
                }
            } else {
                const std::string alibis[] = {
                    "Jaia " + witness + " re jiges koro, kintu amar naam nio na abar!",
                    "Row 3 er meye ra shobai jane ami puro time class ei boshsilam, " + witness + " re jiges koro.",
                    "Ami to shobai k dekhi, " + witness + " o dekhse ami kono fake daak dei nai!"
                };
                response = alibis[v];
            }
            break;
    }

    return response;
}

} // namespace ProxyMystery
