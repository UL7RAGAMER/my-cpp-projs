import requests
import urllib.parse
#ul7ragamer128@outlook.com
#CataClash
def toString(List): 
    return ''.join(List) 

def permute(a, l, r, permutations): 
    if l == r: 
        permutations.append(toString(a)) 
    else: 
        for i in range(l, r): 
            a[l], a[i] = a[i], a[l] 
            permute(a, l+1, r, permutations) 
            a[l], a[i] = a[i], a[l]  # backtrack 

# Generate permutations
string = "_aj_yd"
n = len(string)
a = list(string)
permutations = []
permute(a, 0, n, permutations)

def search_web(query):
    api_key = 'AIzaSyC4UKbMpZxnWBAbJhLA34vUjWoGpYcKp0I'  # Replace with your actual API key
    search_engine_id = 'a2263c3d28a764782'  # The cx value you provided
    encoded_query = urllib.parse.quote(query)
    url = f"https://www.googleapis.com/customsearch/v1?q={encoded_query}&key={api_key}&cx={search_engine_id}"
    
    try:
        response = requests.get(url)
        response.raise_for_status()  # Raise an exception for HTTP errors
        return response.json()
    except requests.exceptions.RequestException as e:
        print(f"HTTP request failed: {e}")
        print(f"URL: {url}")
    except ValueError as e:
        print(f"Error decoding JSON: {e}")
        print(f"URL: {url}")
        print(f"Response content: {response.content}")
    return None

# Test the API call with a simple query
test_query = "example"
result = search_web(test_query)
if result:
    print(f"Search results for {test_query}:")
    print(result)
else:
    print(f"Failed to search for {test_query}")

# Search for each permutation
for perm in permutations:
    result = search_web(perm)
    if result:
        print(f"Search results for {perm}:")
        print(result)
    else:
        print(f"Failed to search for {perm}")
