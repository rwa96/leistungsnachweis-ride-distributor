from sys import argv

def main(inputFile, nRides):
    rides = set()
    with open(inputFile) as fh:
        for line in fh:
            for ride in [int(elm) for elm in line.split(" ")][1:]:
                if ride in rides:
                    print(f':( at {ride}')
                    break
                rides.add(ride)

    if len(rides) != nRides:
        print(':( woanders')
    else: 
        print(':)')


if __name__ == '__main__':
    main(argv[1], int(argv[2]))
