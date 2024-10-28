import React, { useState, useEffect } from 'react';
import { View, StyleSheet, TextInput, Button, FlatList, Text, TouchableOpacity } from 'react-native';
import MapView, { Marker } from 'react-native-maps';
import Geolocation from 'react-native-geolocation-service';
import Icon from 'react-native-vector-icons/FontAwesome';

const Map = () => {
  const [region, setRegion] = useState(null);
  const [search, setSearch] = useState('');
  const [locations, setLocations] = useState([]);
  const [favorites, setFavorites] = useState([]);

  useEffect(() => {
    Geolocation.getCurrentPosition(
      (position) => {
        setRegion({
          latitude: position.coords.latitude,
          longitude: position.coords.longitude,
          latitudeDelta: 0.05,
          longitudeDelta: 0.05,
        });
      },
      (error) => {
        console.log(error);
      },
      { enableHighAccuracy: true, timeout: 15000, maximumAge: 10000 }
    );
  }, []);

  const searchLocations = () => {
    // Lógica para buscar localizações usando uma API, por exemplo, Google Places API
  };

  const addFavorite = (location) => {
    setFavorites([...favorites, location]);
  };

  return (
    <View style={styles.container}>
      {region && (
        <MapView
          style={styles.map}
          region={region}
          onRegionChangeComplete={setRegion}
        >
          {locations.map((location, index) => (
            <Marker
              key={index}
              coordinate={{
                latitude: location.latitude,
                longitude: location.longitude,
              }}
              title={location.name}
            >
              <TouchableOpacity onPress={() => addFavorite(location)}>
                <Icon name="star" size={30} color="gold" />
              </TouchableOpacity>
            </Marker>
          ))}
        </MapView>
      )}
      <View style={styles.searchContainer}>
        <TextInput
          style={styles.searchInput}
          placeholder="Buscar localização"
          value={search}
          onChangeText={setSearch}
        />
        <Button title="Buscar" onPress={searchLocations} />
      </View>
      <FlatList
        data={favorites}
        keyExtractor={(item, index) => index.toString()}
        renderItem={({ item }) => (
          <View style={styles.favoriteItem}>
            <Text>{item.name}</Text>
          </View>
        )}
      />
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    ...StyleSheet.absoluteFillObject,
    justifyContent: 'flex-end',
    alignItems: 'center',
  },
  map: {
    ...StyleSheet.absoluteFillObject,
  },
  searchContainer: {
    position: 'absolute',
    top: 50,
    width: '90%',
    backgroundColor: 'white',
    padding: 10,
    borderRadius: 10,
    shadowColor: '#000',
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.8,
    shadowRadius: 2,
    elevation: 1,
  },
  searchInput: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    marginBottom: 10,
    paddingHorizontal: 10,
  },
  favoriteItem: {
    backgroundColor: 'white',
    padding: 10,
    borderBottomWidth: 1,
    borderColor: '#eee',
  },
});

export default Map;
