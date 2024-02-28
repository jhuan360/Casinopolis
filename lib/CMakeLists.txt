add_library(DeckTestsLibrary
    Card.cpp
    Deck.cpp
)
add_library(CardTestsLibrary
    Card.cpp
)

find_library(M_LIB m)
target_link_libraries(DeckTestsLibrary ${M_LIB})

