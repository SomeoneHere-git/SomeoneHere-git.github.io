import hashlib
import datetime

class AuthService:
    MIN_PASSWORD_LENGTH = 6
    TOKEN_LIFETIME_HOURS = 2

    def __init__(self):
        self._users = {}

    def register(self, email: str, password: str) -> bool:
        if not email or not password or len(password) < self.MIN_PASSWORD_LENGTH:
            return False
        if email in self._users:
            return False  # Користувач вже існує
        
        self._users[email] = self._hash_password(password)
        return True

    def authenticate(self, email: str, password: str) -> dict | None:
        if not email or not password:
            return None
        
        hashed = self._hash_password(password)
        if self._users.get(email) == hashed:
            expires_at = datetime.datetime.utcnow() + datetime.timedelta(hours=self.TOKEN_LIFETIME_HOURS)
            return {
                "token": f"mock-jwt-token-for-{email}",
                "expires_at": expires_at.isoformat() + "Z"
            }
        return None

    def _hash_password(self, password: str) -> str:
        return hashlib.sha256(password.encode('utf-8')).hexdigest()