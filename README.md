import requests

def get_brand_details(brand_name):
    """
    Fetches brand details from Brandfetch API using the given brand name.

    Args:
        brand_name (str): The name of the brand to search.
        client_id (str): Your Brandfetch client ID.

    Returns:
        str: The website link of the brand or an error message.
    """
    client_id = "lvysMbkUuH1l/qe2mmYW4DHhO3e9B0v19xE9ZbOyfgA="
    url = f"https://api.brandfetch.io/v2/search/{brand_name}?c={client_id}"

    response = requests.get(url)

    if response.status_code == 200:
        data = response.json()
        if data and "domain" in data[0]:
            return f"https://{data[0]['domain']}"
        return "Website link not found."
    elif response.status_code == 404:
        return "Brand not found. Please check the brand name."
    else:
        return f"Error: {response.status_code} - {response.text}"

if __name__ == "__main__":
    brand_name = input("Enter the brand name: ")

    result = get_brand_details(brand_name)
    print(f"Result: {result}")
