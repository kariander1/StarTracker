// 
// 
// 

#include "Serializer.h"

void Serializer::SerializeDebug(const String& text)
{
	if(DEBUG)
		Serialize(text);

}
void Serializer::Serialize(const String& text)
{
	Serial.println(text);

}

bool Serializer::ListenForCoordinates(Point &dest_coordinates)
{
   if (Serial.available() > 0) {
        // read the incoming byte:
        String read_string = Serial.readString();
        if (read_string.startsWith(COORDINATES_PREFIX))
        {
            int count = 0;
            float azimuth;
            float elevation;
            char* coordinate = strtok(read_string.c_str(), " ");
            coordinate = strtok(0, " ");
            while (coordinate !=0)
            {
                //Serializer::Serialize(coordinate);
                switch (count)
                {
                case 0:
                    azimuth = atof(coordinate);
                    break;
                case 1:
                    elevation = atof(coordinate);
                    break;
                }
                coordinate = strtok(0, " ");
                count++;
            }
           
            dest_coordinates = Point(azimuth, elevation);
            return true;
        }
        else if (read_string.startsWith(AZIMUTH_PREFIX) )
        {
            char* coordinate = strtok(read_string.c_str(), " ");
            coordinate = strtok(0, " ");
           

            dest_coordinates.x = (atof(coordinate));
            return true;
        }
        else if (read_string.startsWith(ELEVATION_PREFIX))
        {
            char* coordinate = strtok(read_string.c_str(), " ");
            coordinate = strtok(0, " ");


            dest_coordinates.y = (atof(coordinate));
            return true;
        }
       
    }
    return false;
}

