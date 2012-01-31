#ifndef CONF_HPP
#define CONF_HPP
/**
 * @file conf.hpp
 * File where configuration type is implemented.
 *
 * @author Jure Slak <jure.slak@gmail.com>
 * @version 1.0
 */
#include "exceptions.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace tweaksort
{

enum sort_e {
    INSERTIONSORT,
    SELECTIONSORT,
    QUICKSORT,
    HEAPSORT,
    MERGESORT
};

// TODO comment (evilface)
sort_e char_to_enum(char c) {
    switch (c) {
        case 'i': return INSERTIONSORT;
        case 's': return SELECTIONSORT;
        case 'q': return QUICKSORT;
        case 'h': return HEAPSORT;
        case 'm': return MERGESORT;
    }
    return INSERTIONSORT;
}

char enum_to_char(sort_e s) {
    switch (s) {
        case INSERTIONSORT: return 'i';
        case SELECTIONSORT: return 's';
        case QUICKSORT: return 'q';
        case HEAPSORT: return 'h';
        case MERGESORT: return 'm';
    }
    return ' ';
}

/**
 * Class used to represent configuration for main sort routine
 */
struct conf_t {
public:
    typedef std::vector<std::pair<sort_e, size_t>> inner_conf_t;
    inner_conf_t conf;

    /** Default constructor */
    conf_t() : conf() {}

    /**
     * Constructor for class conf_t.
     * @param c Sort character that represents the sort algortithm of first entry
     * @param n Number that limits the first sort algortihm's range
     */
    conf_t(char c, size_t n) : conf() {
        conf.push_back(std::make_pair(char_to_enum(c), n));
    }

    /**
     * Constructor for class conf_t.
     * @param c Sort enumaration number.                                          
     * @param n Number that limits the first sort algortihm's range
     */
    conf_t(sort_e e, size_t n) : conf() {
        conf.push_back(std::make_pair(e, n));
    }

    /**
     * Constructor for class conf_t.
     * @param conf_str String taht represents teh configuration. Might throw errors at parsing.
     */
    conf_t(const std::string& conf_str) : conf() {
        std::stringstream strm(conf_str);
        while (!strm.eof()) {
            char s;
            size_t limit;
            strm.ignore(strm.str().length(), ':');
            strm >> s;
            if (!(s == 'm' || s == 'q' || s == 'h' || s == 'i' || s == 's')) {
                std::stringstream error;
                error << "Unknown sort in configuration: '" << s << "'!" << std::endl;
                throw ParseError(error.str());
            }
            strm.ignore(strm.str().length(), '>');
            if (!strm.eof()) {
                strm >> limit;
                conf.push_back(std::make_pair(char_to_enum(s), limit));
            }
        }
    }

    /**
     * Constructor for class conf_t.
     * @param _conf Vector with conf entries.
     */
    conf_t (inner_conf_t _conf) : conf(_conf) {}

    /**
     * Appends one conf to another.
     * All entries of second conf are added to entries of this.
     * @param o Conf to be appended.
     */
    void operator+=(const conf_t& o);

    /** 
     * Adds two confs.
     * First all entries of first conf are added to the new one, then all the entries of
     * second are appended.
     * @param o Conf to be one of tho summands. The other is this.
     * @return Conf representing the sum.
     */
    conf_t operator+(const conf_t &o) const {
        inner_conf_t c;
        c.insert(c.end(), conf.begin(), conf.end());
        c.insert(c.end(), o.conf.begin(), o.conf.end());
        return conf_t(c);
    }

    /**
     * Standard equality operator.
     * @param o Conf to be compared to this.
     * @return True if completely equal, false otherwise.
     */
    bool operator==(const conf_t& o) const {
        return conf == o.conf;
    }

    /**
     * Printing operator.
     * @param o Output stream, where conf should be printed.
     * @param conf Conf to be printed.
     * @return Output stream with conf appended to it.
     */
    friend std::ostream& operator<<(std::ostream& o, conf_t& conf);

    /**
     * Standard random accecc operator.
     * @param n Index of conf entry wanted. Throws error if invalid.
     * @return Wanted entry.
     */
    template <typename T>
    const std::pair<sort_e, size_t>& operator[](T n) const {
        return conf[n];
    }

    /**
     * Size function.
     * @return Number of entries in conf.
     */
    size_t size() const { return conf.size(); }

    /** 
     * Adds entry to conf.
     * @param c Character respresenting one of sorts.
     * @param n Limit of that sort usage.
     */
    void add_pair(char c, size_t n) {
        conf.push_back(std::make_pair(char_to_enum(c), n));
    }

    /** 
     * Convert to string function.
     * If we have conf c, this must be true:
     * @code
     * conf_t(c.str()).str() == c.str()
     * @endcode
     * Meaning: Output of this function must be valid for parsing it again.
     * Or: This is the inverse of string consrtuctor.
     * @return Conf represented in string.
     */
    std::string str() const {
        std::stringstream str;
        for (size_t i = 0; i < conf.size(); ++i) {
            str << ":" << enum_to_char(conf[i].first) << " --> " << int(conf[i].second) << ";";
        }
        return str.str();
    }

    /**
     * Sets last limit of the sort.
     * @param limit Number respresenting the limit of last sort entry.
     *  @return None.
     */
    void set_last_limit(size_t limit) {
        conf[conf.size()-1].second = limit;
    }

    /**
     * Makes the conf nicer, but with the same meaning.
     * Exaple:
     * :i-->2;:i-->4;:i-->67;:q-->234;:q-->567;:h->-1
     * goes into:
     * :i-->67;:q-->567;:h->-1
     * @return For how many tokens is the conf shorter.
     */
    size_t beautify() {
        if (conf.size() < 1) { return 0; }
        size_t j;
        inner_conf_t c;
        std::pair<sort_e,size_t> previous = conf[0];
        c.push_back(conf[0]);
        for (size_t i = 1; i < conf.size(); ++i) {
            if (conf[i].second == previous.second) { // skip doubled numbers (:i-->10;:q-->10 = :i-->10)
                continue;
            } else if (conf[i].first == previous.first) { //join these two
                c[c.size() - 1].second = conf[i].second;
                ++j;
            } else {
                previous = conf[i];
                c.push_back(conf[i]);
            }
        }
        conf = c;
        return j;
    }

};

std::ostream& operator<< (std::ostream& o, conf_t& conf) {
    o << conf.str();
    return o;
}

void conf_t::operator+=(const conf_t& o) {
    conf.insert(conf.end(), o.conf.begin(), o.conf.end());
}

/**
 * Function testing if output of str method is valid conf.
 */
bool read_write_test() {
    std::string conf = ":q > 5   \n :m -> 116;:h --> -1";
    return conf_t(conf_t(conf).str()).str() == conf_t(conf).str();
}

}
#endif
