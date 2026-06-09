from flask import Flask, request, jsonify
from auth_service import AuthService

app = Flask(__name__)
auth_service = AuthService()

auth_service.register("test@nure.ua", "password123")

@app.route('/health', methods=['GET'])
def health():
    """Ендпоїнт для перевірки працездатності сервісу (Health Check)"""
    return jsonify({"status": "healthy"}), 200

@app.route('/api/auth/login', methods=['POST'])
def login():
    """Основний ендпоїнт для бізнес-логіки аутентифікації"""
    data = request.get_json() or {}
    email = data.get("email")
    password = data.get("password")

    if not email or not password:
        return jsonify({"error": "Missing email or password"}), 400

    result = auth_service.authenticate(email, password)
    if result:
        return jsonify(result), 200
    
    return jsonify({"error": "Invalid credentials"}), 401

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)